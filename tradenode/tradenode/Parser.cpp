#include "Parser.h"
#include <stack>
#include <ctype.h>
#include <assert.h>
using std::stack;

PTree::PTree()
{
	tp = IVAL;
	ival = 0;
	return;
}

PTree::~PTree()
{
	return;
}

vector<Token> tokenizer(const string input)
{
	vector<Token> result;
	char eqt = '=';
	char ltk = '{';
	char rtk = '}';
	Token curtok;
	char buf[512];
	int bufcounter = 0;
	for (int i = 0; i < 512; i++)
	{
		buf[i] = 0;
	}
	int flag = 0;
	for (auto c = input.begin(); c != input.end();c++)
	{
		if (flag == 0) // looking for a new token
		{
			assert(bufcounter == 0);
			if (isspace(*c)) continue;
			if (*c == '=')
			{
				curtok.tok = EQTOK;
				curtok.value = "";
				result.push_back(curtok);
				flag = 0;
				continue;
			}
			if (*c == '{')
			{
				curtok.tok = LFTOK;
				curtok.value = "";
				result.push_back(curtok);
				flag = 0;
				continue;
			}
			if (*c == '}')
			{
				curtok.tok = RTTOK;
				curtok.value = "";
				result.push_back(curtok);
				flag = 0;
				continue;
			}
			if (isalnum(*c) || *c=='.' || *c == '_')
			{
				while (isalnum(*c) || *c == '.' || *c == '_')
				{
					buf[bufcounter] = *c;
					bufcounter++;
					c++;
				}
				curtok.tok = STRTOK;
				curtok.value = buf;
				result.push_back(curtok);
				// reset buffer
				for (int i = 0; i < 512; i++)
				{
					buf[i] = 0;
				}
				bufcounter = 0;
				if (*c == '=' || *c == '{' || *c == '}') c--;
			}
			if (*c == '\"')
			{
				buf[bufcounter] = *c;
				bufcounter++;
				c++;
				while (*c != '\"')
				{
					buf[bufcounter] = *c;
					bufcounter++;
					c++;
				}
				buf[bufcounter] = *c;
				curtok.tok = STRTOK;
				curtok.value = buf;
				result.push_back(curtok);
				// reset buffer
				for (int i = 0; i < 512; i++)
				{
					buf[i] = 0;
				}
				bufcounter = 0;
				if (*c == '=' || *c == '{' || *c == '}') c--;
			}
		}

	}
	return result;
}

/* Helper function used to identify a value's type */
static ValType identify_type(string input) {
	bool isFloat = false;
	bool isNum = true;
	for (auto c : input)
	{
		if (!isdigit(c))
		{
			if (c == '.' && isFloat == false)
			{
				isFloat = true;
			}
			else
			{
				isNum = false;
				break;
			}
		}

	}
	if (!isNum)
	{
		return SVAL;
	}
	else
	{
		if (isFloat)
		{
			return DVAL;
		}
		else
		{
			return IVAL;
		}
	}
}

/*	Parse input from tokens
	Patterns modes include
	1. STRTOK EQTOK STRTOK
	2. STRTOK EQTOK LFTOK [STRTOK] RTTOK
	3. STRTOK EQTOK LFTOK [1 || 2] RTTOK

*/
enum ParserState {
	LOOK_NEWELEM, // eminent element must be strtok, will create new subtree, switch context
	LOOK_EQ, // eminent element must be eqtok
	AFTER_EQ, // should be strtok or lftok
		  // if strtok -> save -> FINISH_CUR
		  // if lftok -> INCUR_DISCOVER
	INCUR_DISCOVER, // will perform check to see list of val or chil
			// list -> INCUR_LIST, chil -> (save context) LOOK_NEWELEM
	INCUR_LIST, // in list of elem
	FINISH_CUR // will return to last in stack, switch context
};

PTree * parse_config(const string input)
{
	vector<Token> tokens = tokenizer(input);
	PTree *root = new PTree;
	PTree *cur_tree = root;
	root->tp = CHIL;
	stack<PTree*> tree_stack;
	tree_stack.push(root);
	int mode = 1;
	ParserState state = LOOK_NEWELEM;

	for (auto tok = tokens.begin(); tok != tokens.end(); tok++)
	{
		auto tempt = tok;
		bool getEqual = false;
		switch (state)
		{
		case LOOK_NEWELEM:
			if (tok->tok == STRTOK)
			{
				// save context, context switch
				PTree *new_tree = new PTree;
				cur_tree->children.push_back(new_tree);
				new_tree->name = tok->value;
				tree_stack.push(cur_tree);
				cur_tree = new_tree;
				// state change
				state = LOOK_EQ;
			}
			else if (tok->tok == RTTOK)
			{
				state = FINISH_CUR;
				// compensation
				tok--;
			}
			break;
		case LOOK_EQ:
			assert(tok->tok == EQTOK);
			state = AFTER_EQ;
			break;
		case AFTER_EQ:
			if (tok->tok == STRTOK)
			{
				switch (identify_type(tok->value))
				{
				case IVAL:
					cur_tree->tp = IVAL;
					cur_tree->ival = std::stoi(tok->value, nullptr);
					state = FINISH_CUR;
					break;
				case DVAL:
					cur_tree->tp = DVAL;
					cur_tree->dval = std::stod(tok->value, nullptr);
					state = FINISH_CUR;
					break;
				case SVAL:
					cur_tree->tp = SVAL;
					cur_tree->sval = tok->value;
					state = FINISH_CUR;
					break;
				default:
					break;
				}
				// compensation
				tok--;
			}
			else if (tok->tok == LFTOK)
			{
				state = INCUR_DISCOVER;
				break;
			}
			break;
		case INCUR_DISCOVER:
			// discover the mode in the curly
			while (tempt->tok != RTTOK)
			{
				if (tempt->tok == EQTOK)
				{
					getEqual = true;
					break;
				}
				tempt++;
			}

			if (getEqual) // we need to find a new elem
			{
				state = LOOK_NEWELEM;
				cur_tree->tp = CHIL;
				// compensate for extra tok increment
				tok--;
				break;
			}
			else // we are in list of value
			{
				ValType eltp = identify_type((tok)->value);
				if (eltp == IVAL)
				{
					cur_tree->tp = IVALLIST;
				}
				else if (eltp == DVAL)
				{
					cur_tree->tp = DVALLIST;
				}
				else // type is sval
				{
					cur_tree->tp = SVALLIST;
				}
				state = INCUR_LIST;
				// compensate for extra tok increment
				tok--;
				break;
			}
			break;
		case INCUR_LIST:
			if (tok->tok != RTTOK)
			{
				ValType mytp = cur_tree->tp;
				if (mytp == IVALLIST)
				{
					cur_tree->ilist.push_back(std::stoi(tok->value, nullptr));
				}
				else if (mytp == DVALLIST)
				{
					cur_tree->dlist.push_back(std::stod(tok->value, nullptr));
				}
				else if (mytp == SVALLIST)
				{
					cur_tree->slist.push_back(tok->value);
				}
				break;
			}
			else
			{
				state = FINISH_CUR;
				// compensation
				tok--;
				break;	
			}
			break;
		case FINISH_CUR:
			// switch context to previous tree
			cur_tree = tree_stack.top();
			tree_stack.pop();
			state = LOOK_NEWELEM;
			break;
		default:
			break;
		}
	}
	 

	return root;
}

Token::Token()
{
}

Token::~Token()
{
}
