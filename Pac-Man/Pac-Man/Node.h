#ifndef NODE_H
#define NODE_H

#include "stdafx.h"
#include <vector>

class Node {
public:
	int ID;
	float CX, CY;
	vector<Node*> Adj;

	Node(int,float, float);
	Node(const Node *);
	Node(int, float, float, vector<Node*>);
	Node* operator= (const Node*);
	~Node();

	void addEdge(Node *);
	char NodeDirection(Node *);
	Node* getNext(char);
	bool isNotOption(char);
};

#endif // !NODE_H

