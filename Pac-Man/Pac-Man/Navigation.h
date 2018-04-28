#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "stdafx.h"
#include "Node.h"

#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

class Navigation {
public:
	Node * StartNode;
	void (Navigation::*DIR)();
	vector<Node*> List;

	Navigation();
	~Navigation();

	void Initialize();

	void XInc();
	void XDec();
	void YInc();
	void YDec();
	void Idle();
};

#endif // !NAVIGATION_H
