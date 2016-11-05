#include <vector>
#include <list>
#include <iostream>
using std::vector;
using std::list;
struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	int maxPoints(vector<Point>& points) {
		int n = points.size();
		vector<vector<float>> slopearr;
		for (int i = 0; i < n; i++)
		{
			vector<float> line;
			for (int j = 0; j < n; j++)
			{
				line.push_back(0);
			}
			slopearr.push_back(line);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{

				}
			}
		}
	}
};