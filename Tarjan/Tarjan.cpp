// Tarjan.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <stack>
#include "limits.h"

using namespace std;

int numNodes;
int numEdges;


struct Node{
	int id;
	vector<Node *>  * adjacentNodes;
};

void explore(bitset<200> & exploredBitset, vector<Node *> & nodesList, vector<Node *> & finishingTimesVector, int i);
vector<Node *> findFinishingTimes(vector<Node *> nodesList);


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
	for(int i = 0; i < nodesList.size(); i++){
		Node * newNode = new Node;
		newNode->id = i+1;
		newNode->adjacentNodes = new vector<Node *>;
		nodesList[i] = newNode;
	}
	while(graphFile.good()){
		getline(graphFile, line, ' ');
		getline(graphFile, line1, '\n');
		node1 = atoi(line.c_str());
		node2 = atoi(line1.c_str());
		cout << node1 << " " << node2 << endl;
		(*(nodesList[node2 - 1]->adjacentNodes)).push_back(nodesList[node1 - 1]);
	} 

	for(int i=0; i<numNodes; i++){
		int numAdjNodes = (*(nodesList[i]->adjacentNodes)).size();
		cout << "NODE: " << i + 1 << endl;
		for(int j=0; j < numAdjNodes; j++){
			cout << "Adjacent Nodes: " << (((*(nodesList[i]->adjacentNodes))[j])->id) << endl;
		}
	}
	cout << endl << endl << endl;

	vector<Node *> nodesFinishingTimeList = findFinishingTimes(nodesList);
}

vector<Node *> findFinishingTimes(vector<Node *> nodesList){
	bitset<200> exploredBitset;
	vector<Node *> finishingTimesVector;
	for(int i = 0; i < numNodes; i++){
		if(!exploredBitset[i]){
			explore(exploredBitset, nodesList, finishingTimesVector, i);
		}
	}
	for(int i = 0; i < finishingTimesVector.size(); i++){
		cout << i + 1 << "TO FINISH:" << endl;
		cout << finishingTimesVector[i]->id << endl;
	}
	return finishingTimesVector;
}

void explore(bitset<200> & exploredBitset, vector<Node *> & nodesList, vector<Node *> & finishingTimesVector, int i){
	stack<Node *> myStack;
	myStack.push(nodesList[i]); //initializes the stack to have the source node for this function call
	while(!myStack.empty()){ //iterates while the stack is not empty
		Node * currentNode = myStack.top();	//Peeks at the top of the stack (without actually removing the top node), and sets it as the current one
		exploredBitset[currentNode->id] = 1;
		bool hasOutlets = false;
		for(int j = 0; j < (*(currentNode->adjacentNodes)).size(); j ++){ //Iterates through the adjacent nodes of that node
			int bitSetCheckId = (*((*(currentNode->adjacentNodes))[j])).id; //grabs the id of each adjacent node
			if(!exploredBitset[bitSetCheckId]){ //checks to see if each adjacent node has already been explored
				myStack.push((*(currentNode->adjacentNodes))[j]); // if not, Pushes the newly discovered node to the top of the stack
				hasOutlets = true; //lets the program know that this is not a dead end node
			}
		}
		if(!hasOutlets){
			myStack.pop(); //pops it off the stack if it has no outlets
			finishingTimesVector.push_back(currentNode);//adds it to the new finishing times vector
		}
	}
}

