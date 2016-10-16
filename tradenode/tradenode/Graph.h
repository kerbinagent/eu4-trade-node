#ifndef GRAPH_HEAD
#define GRAPH_HEAD
#include <vector>
#include "TradeNode.h"
using std::vector;
class MyNode {
public:
	MyNode(int i);
	int getDistance();
	void discoverIt();
	bool isDiscovered();
	void increaseDistance();
	void setDistance(int x);
	// using nodeId
	vector<int> adjacencies;
	// using nodeId
	int parent;
private:
	int nodeId;
	int distanceFrom;
	bool discovered;
};
class MyGraph {
public:
	MyGraph();
	int findPath(int startID, int endID, int maxTries);
	void pushNode(int nodeId, vector<int> adj);
	void modifyAdj(int nodeId, vector<int> newadj);
	void addAdj(int nodeId, int adjId);
	void writePath(int endID, int startID, int* pOutBuffer, int steps);
private:
	vector<MyNode> allNodes;
};

MyGraph buildGraph(vector<TradeNode> input);

//MyGraph center_graph(MyGraph graph, int startID);
#endif