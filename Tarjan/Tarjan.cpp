// Tarjan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <n

using namespace std;

int numNodes;
int numEdges;

struct Node{
	int id;
	vector<Node *>  * adjacentNodes;
};

int _tmain(int argc, _TCHAR* argv[]){
	ifstream graphFile("example.txt");
	string line;
	string line1;
	int node1;
	int node2;
	getline(graphFile, line);
	numNodes = atoi(line.c_str());
	getline(graphFile, line);
	numEdges = atoi(line.c_str());
	vector<Node *> nodesList;
	nodesList.resize(numNodes);
	if(nodesList.at(1)==NULL)
		cout<<"it's empty!"<<endl;
	/**
	while(graphFile.good()){
		getline(graphFile, line, ' ');
		getline(graphFile, line1, ' ');
		node1 = atoi(line.c_str());
		node2 = atoi(line1.c_str());
	} */
}

