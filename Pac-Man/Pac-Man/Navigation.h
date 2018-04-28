#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "Node.h"

class Navigation {
public:
	void (Navigation::*DIR)();

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
