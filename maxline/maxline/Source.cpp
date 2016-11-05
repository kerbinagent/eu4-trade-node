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
		if (n < 2) return n;
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
					slopearr[i][j] = -3;
				}
				else
				{
					if (slopearr[i][j] == -2)
					{
						if (points[j].x - points[i].x == 0)
						{
							slopearr[i][j] = -1;
						}
						else
						{
							slopearr[i][j] = abs(((float) points[j].y - (float) points[i].y) / ( (float) points[j].x - (float) points[i].x));
						}
						
					}
				}
			}
		}
		int max = 2;
		for (int i = 0; i < n; i++)
		{
			int count = 2;
			std::sort(slopearr[i].begin(), slopearr[i].end());
			for (int j = 1; j < n; j++)
			{
				if (slopearr[i][j] == slopearr[i][j - 1])
				{
					count++;
					if (count > max) max = count;

				}
				else
				{
					if (count > max) max = count;
					count = 2;
				}
			}
		}
		return max;
	}
};

int main() {
	Solution sol;
	Point pt1 = Point(0, 0);
	Point pt2 = Point(1, 1);
	Point pt3 = Point(2, 2);
	Point pt4 = Point(4, 4);
	vector<Point> pts = {pt1, pt2, pt3, pt4};
	std::cout << sol.maxPoints(pts) << std::endl;
	return 0;
}