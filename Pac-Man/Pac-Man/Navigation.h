#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "stdafx.h"
#include "Node.h"
#include "Object.h"

#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Navigation {
public:
	Node * StartNode;
	vector<Node*> List;

	Navigation();
	~Navigation();

	void Initialize();
};

#endif // !NAVIGATION_H
