#ifndef PARSER_H__
#define PARSER_H__
#include <vector>
#include <string>
using std::string;
using std::vector;
class PTree {
public:
	PTree();
	~PTree();
	string name;
	enum ValType {
		IVAL, 
		DVAL,
		SVAL,
		CHIL
	};
	ValType tp;
	union
	{
		int ival;
		double dval;
		string sval;
		vector<PTree *> children;
	};

};

#endif // !PARSER_H__
