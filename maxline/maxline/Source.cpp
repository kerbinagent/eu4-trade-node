#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
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
				line.push_back(-2);
			}
			slopearr.push_back(line);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					slopearr[i][j] = -1;
				}
				else
				{
					if (slopearr[i][j] == -2)
					{
						slopearr[i][j] = abs((points[j].y - points[i].y) / (points[j].x - points[i].x));
					}
				}
			}
		}
		int max = 0;
		for (int i = 0; i < n; i++)
		{
			int count = 0;
			std::sort(slopearr[i].begin(), slopearr[i].end());
			for (int j = 1; j < n; j++)
			{
				if (slopearr[i][j] == slopearr[i][j - 1])
				{
					count++;
				}
				else
				{
					if (count > max) max = count;
					count = 0;
				}
			}
		}
		return max;
	}
};