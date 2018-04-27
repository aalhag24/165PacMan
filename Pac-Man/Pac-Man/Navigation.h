#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Node.h"

class Navigation {

/* THIS SHOULD BE IN PLAYER AND ENEMY

Node * curr;
Node * prev;

typedef float(*fptr)();
*/

public:
	Navigation();
	~Navigation();

	void Initialize();

	void XInc();
	void XDec();
	void YInc();
	void YDec();
};

#endif // !NAVIGATION_H
