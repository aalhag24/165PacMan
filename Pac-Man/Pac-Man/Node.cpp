#include "stdafx.h"
#include "Node.h"

Node::Node(int n, float x, float y){
	CX = x; CY = y;
	ID = n;
}

Node::Node(const Node *a){
	CX = a->CX;
	CY = a->CY;
	ID = a->ID;

	Adj = a->Adj;
}

Node::Node(int id, float x, float y, vector<Node*> adj){
	CX = x;
	CY = y;
	ID = ID;

	vector<Node*>::iterator itt = Adj.begin();
	for (vector<Node*>::iterator it = adj.begin(); it != adj.end(); ++it) {
		Adj.push_back((*it));
	}
}

Node * Node::operator=(const Node *a){
	CX = a->CX;
	cout << a->CX << " " << CX << endl;
	CY = a->CY;
	ID = a->ID;

	Adj = a->Adj;
	return this;
}

Node::~Node(){
	Adj.clear();
}

/// DOUBLE CHECK THIS WORKS
void Node::addEdge(Node *a){
	Adj.push_back(a);
}

char Node::NodeDirection(Node* a){
	if (a == nullptr) {
		return ' ';
	}

	if (CX < a->CX) { return 'R'; }
	else if (CX > a->CX) { return 'L'; }
	if (CY < a->CY) { return 'U'; }
	else if (CY > a->CY) { return 'D'; }
	else { return ' '; }
}

Node * Node::getNext(char D){
	std::vector<Node*>::iterator it = Adj.begin();
	for (; it != Adj.end(); ++it) {
		if (NodeDirection((*it)) == D)
			return (*it);
	}
	return nullptr;
}

bool Node::isNotOption(char D) {
	std::vector<Node*>::iterator it = Adj.begin();
	for (; it != Adj.end(); ++it) {
		if (NodeDirection((*it)) == D)
			false;
	}
	return true;
}