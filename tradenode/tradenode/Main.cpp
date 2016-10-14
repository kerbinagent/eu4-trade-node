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
	std::cout << "EU4 Trade Node Map Explorer" << std::endl;

	// init IO operation
	ifstream vanilla;
	vanilla.open("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Europa Universalis IV\\common\\tradenodes\\00_tradenodes.txt");
	string line;
	string entire_file("");
	while (std::getline(vanilla, line)) {
		entire_file.append(line);
		entire_file.append("\n");
	}
	std::cout << entire_file;
	vanilla.close();
	PTree mytree;
	while (std::cin >> cmd) {
	}
	return 0;
}