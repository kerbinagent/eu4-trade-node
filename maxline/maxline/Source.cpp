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
		vector<vector<struct Record>> slopearr;
		for (int i = 0; i < n; i++)
		{
			vector<struct Record> line;
			for (int j = 0; j < n; j++)
			{
				struct Record rec;
				line.push_back(rec);
			}
			slopearr.push_back(line);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
 				if (i == j)
				{
					slopearr[i][j].type = 0;
				}
				else
				{
					if (slopearr[j][i].calculated == true)
					{
						slopearr[i][j] = slopearr[j][i];
					}
					else
					{
						if (points[j].x - points[i].x == 0)
						{
							slopearr[i][j].type = 2;
						}
						else
						{
							int realj, reali;
							realj = (points[j].x > points[i].x ? j : i);
							reali = realj == j ? i : j;
							slopearr[i][j].slope = (((float) points[realj].y - (float) points[reali].y) / ( (float) points[realj].x - (float) points[reali].x));
							slopearr[i][j].type = 1;
						}
						slopearr[i][j].calculated = true;
					}
				}
			}
		}
		int max = 2;
		for (int i = 0; i < n; i++)
		{
			int count = 2;
			std::sort(slopearr[i].begin(), slopearr[i].end(), customLess);
			for (int j = 1; j < n; j++)
			{
				if (slopearr[i][j].type == slopearr[i][j - 1].type && slopearr[i][j].slope == slopearr[i][j-1].slope)
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
private:
	struct Record {
		int type;
		float slope;
		bool calculated;
		Record() : calculated(false), slope(0) {}
	};
	struct {
		bool operator()(struct Record a, struct Record b)
		{
			if (a.type == 0) return true;
			if (a.type == 1) return false;
			return (a.slope < b.slope);
		}
	} customLess;
};

int main() {
	Solution sol;
	Point pt1 = Point(0, 0);
	Point pt2 = Point(1, 1);
	Point pt3 = Point(1, -1);
	Point pt4 = Point(4, 4);
	vector<Point> pts = {pt1, pt2, pt3};
	std::cout << sol.maxPoints(pts) << std::endl;
	return 0;
}