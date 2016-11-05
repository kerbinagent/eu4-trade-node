#ifndef TradeNode_H__
#define TradeNode_H__
#include <vector>
#include <string>
#include "Parser.h"
using std::vector;
using std::string;
class TradeNode;
class LinkRecord;
class LinkRecord
{
public:
	LinkRecord();
	~LinkRecord();
	TradeNode *target;
	bool isOut;
	vector<int> path;

};
class TradeNode
{
public:
	TradeNode();
	~TradeNode();
	string name;
	int nodeid;
	int location;
	int color[3];
	vector<int> members;
	vector<LinkRecord> links;
	bool inland;
	bool end;
};

vector<TradeNode> getAllNodes(PTree *tree);

string printNode(TradeNode input);

#endif // !TradeNode_H__
