#ifndef OBJECT_H
#define OBJECT_H

#include "TexRect.h"
#include "AnimatedRect.h"

class Object {
public:
	float X, Y, W, H;
	TexRect * Image;

	virtual void draw() = 0;
	virtual bool contains(const Object &) = 0;
};

#endif // !OBJECT_H

