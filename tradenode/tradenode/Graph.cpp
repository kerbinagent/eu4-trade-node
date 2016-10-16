#include "Graph.h"
#include <queue>
using std::queue;

MyNode::MyNode(int i) {
	nodeId = i;
	distanceFrom = -1;
	parent = -1;
	discovered = false;
	return;
}

int MyNode::getDistance()
{
	return distanceFrom;
}

void MyNode::discoverIt()
{
	discovered = true;
}

bool MyNode::isDiscovered()
{
	return discovered;
}

void MyNode::increaseDistance()
{
	distanceFrom++;
}

void MyNode::setDistance(int x)
{
	distanceFrom = x;
}

MyGraph::MyGraph()
{
	return;
}

int MyGraph::findPath(int startID, int endID, int maxTries)
{
	queue<int> exploreQ;
	exploreQ.push(startID);
	allNodes[startID].setDistance(0);
	int current;
	while (!exploreQ.empty()) {

		// dequeue current
		current = exploreQ.front();
		exploreQ.pop();
		//if (allNodes[current].getDistance() == maxTries) continue;

		// explore current
		for (int x : allNodes[current].adjacencies) {
			if (!allNodes[x].isDiscovered()) {
				// not discovered
				allNodes[x].discoverIt();
				allNodes[x].setDistance(allNodes[current].getDistance() + 1);
				allNodes[x].parent = current;
				exploreQ.push(x);
				// reach destination
				if (x == endID) return (allNodes[x].getDistance());
			}
		}
	}
	return -1;
}

void MyGraph::exploreGraph(int startID)
{
	queue<int> exploreQ;
	exploreQ.push(startID);
	allNodes[startID].setDistance(0);
	allNodes[startID].discoverIt();
	int current;
	while (!exploreQ.empty()) {

		// dequeue current
		current = exploreQ.front();
		exploreQ.pop();
		//if (allNodes[current].getDistance() == maxTries) continue;

		// explore current
		for (int x : allNodes[current].adjacencies) {
			if (!allNodes[x].isDiscovered()) {
				// not discovered
				allNodes[x].discoverIt();
				allNodes[x].setDistance(allNodes[current].getDistance() + 1);
				allNodes[x].parent = current;
				exploreQ.push(x);
			}
		}
	}
	return;
}

void MyGraph::pushNode(int nodeId, vector<int> adj)
{
	MyNode node(nodeId);
	node.adjacencies = adj;
	allNodes.push_back(node);
}

void MyGraph::modifyAdj(int nodeId, vector<int> newadj)
{
	allNodes[nodeId].adjacencies = newadj;
	return;
}

void MyGraph::addAdj(int nodeId, int adjId)
{
	allNodes[nodeId].adjacencies.push_back(adjId);
	return;
}

// steps is used to write result backwards
void MyGraph::writePath(int endID, int startID, int * pOutBuffer, int steps)
{
	int current = endID; int i = steps - 1;
	while (current != startID) {
		pOutBuffer[i] = current;
		current = allNodes[current].parent;
		i--;
	}
	return;
}

MyGraph buildGraph(vector<TradeNode> input)
{
	MyGraph result;
	for (auto n : input)
	{
		vector<int> nodeadj;
		for (auto l : n.links)
		{
			nodeadj.push_back(l.target->nodeid);
		}
		result.pushNode(n.nodeid, nodeadj);
	}
	return result;
}
