#ifndef NODE_H
#define NODE_H

#include <vector>
#include "stdafx.h"

class Node {
	string Name;
	float CX, CY;
public:

	Node(string,float, float);
	Node(const Node &);
	~Node();

	vector<Node*> adj;
	void addEdge(Node *);
	char NodeDirection(const Node &);
};

#endif // !NODE_H

