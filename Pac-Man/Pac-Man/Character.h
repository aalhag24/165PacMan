#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"

class Character : public Object {

public:
	void draw();
	bool contains(const Object &);
};

#endif // !CHARACTER_H
