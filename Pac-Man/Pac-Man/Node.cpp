#include "Node.h"

Node::Node(string n, float x, float y){
	CX = x; CY = y;
	Name = n;
}

Node::Node(const Node &a){
	CX = a.CX;
	CY = a.CY;
	Name = a.Name;
}

Node::~Node(){
	for (std::vector<Node*>::iterator it = adj.begin(); it != adj.end(); ++it)
		delete (*it);
	adj.clear();
}

/// DOUBLE CHECK THIS WORKS
void Node::addEdge(Node *a){
	adj.push_back(a);
}

char Node::NodeDirection(const Node& a) {
	if (CX > a.CX) { return 'L';  }
	else if (CX < a.CX) { return 'R'; }
	else if (CY > a.CY) { return 'D'; }
	else if (CY > a.CY) { return 'U'; }
}
