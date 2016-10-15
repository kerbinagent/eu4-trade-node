#ifndef PARSER_H__
#define PARSER_H__
#include <vector>
#include <string>
using std::string;
using std::vector;
enum ValType {
	IVAL,
	DVAL,
	SVAL,
	IVALLIST,
	DVALLIST,
	SVALLIST,
	CHIL
};
class PTree {
public:
	PTree();
	~PTree();
	string name;
	ValType tp;
	union
	{
		int ival;
		double dval;
		string sval;
		vector<int> ilist;
		vector<double> dlist;
		vector<string> slist;
		vector<PTree *> children;
	};
	

};
enum Tok {
	STRTOK,
	EQTOK,
	LFTOK,
	RTTOK
};
class Token {
public:
	Token();
	~Token();
	Tok tok;
	string value;
};
vector<Token> tokenizer(const string input);

PTree *parse_config(const string input);

#endif // !PARSER_H__
