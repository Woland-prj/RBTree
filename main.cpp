#include <iostream>
#include <fstream>
#include "RBTree.h"
#include <string>

int main() {
	RBTree tree;
	std::string data;
	std::ifstream in_file("in.txt");

	getline(in_file, data);
	for (size_t i = 0;i < data.length();i++) {
		tree.Insert(data[i] - '0');
	}

	tree.Print();
}