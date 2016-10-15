#include "TradeNode.h"
#include <assert.h>
#include <algorithm>
LinkRecord::LinkRecord()
{
}

LinkRecord::~LinkRecord()
{
}

TradeNode::TradeNode()
{
	inland = false;
	end = false;
}

TradeNode::~TradeNode()
{
}

vector<TradeNode> getAllNodes(PTree * tree)
{
	vector<TradeNode> result;
	vector<string> all_names;
	int i = 0;
	// deal with everything except LinkRecord
	vector<PTree *> looper = tree->children;
	for (auto t : looper)
	{
		TradeNode cur;
		// set name
		cur.name = (t)->name;
		all_names.push_back((t)->name);
		cur.nodeid = i;
		vector<PTree *> second_looper = t->children;
		for (auto o : second_looper)
		{
			// parse options
			if (o->name == "location")
			{
				cur.location = o->ival;
			}
			else if (o->name == "color")
			{
				for (int j = 0; j < 3; j++)
				{
					cur.color[j] = o->ilist[j];
				}
			}
			else if (o->name == "members")
			{
				cur.members = o->ilist;
			}
			else if (o->name == "inland")
			{
				cur.inland = true;
			}
			else if (o->name == "end")
			{
				cur.end = true;
			}

		}
		result.push_back(cur);
		i++;
	}

	i = 0;
	for (auto t : looper)
	{
		vector<PTree *> second_looper = t->children;
		for (auto o : second_looper)
		{
			if (o->name == "outgoing")
			{
				LinkRecord outRecord;
				LinkRecord inRecord;
				inRecord.target = &result[i];
				inRecord.isOut = false;
				vector<int> long_path;
				long_path.push_back(result[i].location);
				int j;
				auto third_looper = o->children;
				for (auto r : third_looper)
				{
					if (r->name == "name")
					{
						// look for the one with that name in existing node
						for (j = 0; j < result.size(); j++)
						{
							if (all_names[j] == r->sval.substr(1, r->sval.size() - 2)) break;
						}
						assert(all_names[j] == r->sval.substr(1, r->sval.size() - 2));
						outRecord.target = &result[j];

						
					}
					if (r->name == "path")
					{
						auto another_looper = r->ilist;
						for (auto n : another_looper)
						{
							long_path.push_back(n);
						}
					}
				}
				outRecord.path = long_path;
				outRecord.isOut = true;
				std::reverse(long_path.begin(), long_path.end());
				inRecord.path = long_path;
				result[i].links.push_back(outRecord);
				result[j].links.push_back(inRecord);
			}
		}
		i++;
	}
	return result;
}
