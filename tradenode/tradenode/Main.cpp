#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"
using std::string;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
#define BUFFERSIZE 128
int main()
{
	string cmd;
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
	delete full_tree;

	cout << "complete." << endl;

	while (std::cin >> cmd) {
	}
	return 0;
}