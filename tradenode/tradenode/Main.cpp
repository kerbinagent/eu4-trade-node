#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"
#include "TradeNode.h"
#include "Graph.h"
using std::string;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
#define BUFFERSIZE 128
int main()
{
	cout << "EU4 Trade Node Map Explorer" << endl;

	// init IO operation
	std::cout << "Reading from vanilla file...";
	ifstream vanilla;
	vanilla.open("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Europa Universalis IV\\common\\tradenodes\\00_tradenodes.txt");
	string line;
	string entire_file("");
	while (std::getline(vanilla, line)) {
		entire_file.append(line);
		entire_file.append("\n");
	}
	cout << "complete." << endl;
	vanilla.close();

	// Parsing
	std::cout << "Parsing vanilla file...";
	PTree mytree;
	//vector<Token> result = tokenizer(entire_file);
	PTree *full_tree = parse_config(entire_file);
	vector<TradeNode> original_nodes = getAllNodes(full_tree);
	delete full_tree;
	MyGraph original_graph = buildGraph(original_nodes);
	cout << "complete." << endl;

	// simple repl
	string cmd;
	bool van = true;
	string current_center;
	vector<TradeNode> cur_map;
	cur_map = original_nodes;
	while (std::getline(std::cin, cmd)) {
		if (cmd == "where")
		{
			if (van) {
				cout << "This is the vanilla trade node config" << endl;
			}
			else
			{
				cout << "This is config centered around " << current_center<< endl;
			}
		}
		else if (cmd == "vanilla")
		{
			van = true;
			cur_map = original_nodes;
		}
		else if (cmd == "ls")
		{
			for (auto n : original_nodes)
			{
				cout << n.name << endl;
			}
		}
		else if (cmd == "center" || cmd == "c")
		{
			cout << "Please provide a new center" << endl;	
			int centerid;
			cin >> centerid;
			MyGraph newg = original_graph;
			newg.exploreGraph(centerid);
			cur_map = newg.toTradeNodes(original_nodes);
			cout << "New config generated" << endl;
			van = false;
			current_center = cur_map[centerid].name;
		}
		else if (cmd == "s" || cmd == "search")
		{
			cout << "Please provide a search string" << endl;
			string searchkey;
			cin >> searchkey;
			cout << endl;
			for (auto n : original_nodes) 
			{
				auto found = n.name.find(searchkey);
				if (found != std::string::npos) cout << n.name << " " << n.nodeid << endl;
			}
		}
		else if (cmd == "p" || cmd == "print")
		{
			cout << "Please provide an id for print" << endl;
			int nodeid;
			cin >> nodeid;
			cout << printNode(cur_map[nodeid]) << endl;
		}
		else if (cmd == "o" || cmd == "out")
		{
			if (van) continue;
			string outpath = "centered_at_";
			outpath.append(current_center);
			outpath.append(".txt");
			cout << "Writing to " << outpath << "...";
			std::ofstream outf;
			outf.open(outpath, std::fstream::out);
			for (auto n : cur_map)
			{
				outf << printNode(n);
			}
			cout << "complete" << endl;
			outf.close();
		}
		else if (cmd == "q" || cmd == "quit")
		{
			return 0;
		}
	}
	return 0;
}