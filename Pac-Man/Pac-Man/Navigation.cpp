#include "stdafx.h"
#include "Navigation.h"

Navigation::Navigation(){
}

Navigation::~Navigation(){
	StartNode = NULL;
	delete StartNode;

	for (vector<Node*>::iterator it = List.begin(); it != List.end(); ++it) {
		(*it) = NULL;
		delete (*it);
	}
}

void Navigation::Initialize(){
	ifstream inFile;
	int Num, ID, pos = 0; float XVal, YVal, NAdj;
	ifstream myfile("Nodes.txt", ios::out | ios::binary);

	if (!myfile.is_open()) {
		cout << "Unable to open file";
		exit(1);
	}

	while (myfile.is_open()) {
		myfile >> Num >> XVal;
		if (Num == 101)
			break;
		for (int i = 0; i < Num; i++) {
			myfile >> ID >> YVal;
			Node *p = new Node(ID, XVal, YVal);
			List.push_back(p);
		}
	}

	while (myfile.is_open()) {
		myfile >> Num >> NAdj;
		if(Num == 102)
			break;
		for (int i = 0; i < NAdj; i++) {
			myfile >> pos;
			List[Num]->addEdge(List[pos]);
		}
	}

	StartNode = List[0];
	LeftEdge = List[5];
	RightEdge = List[12];

	inFile.close();
}

