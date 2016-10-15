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

PTree * parse_config(const string input)
{
	
	return nullptr;
}

Token::Token()
{
}

Token::~Token()
{
}
