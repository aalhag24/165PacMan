#ifndef OBJECT_H
#define OBJECT_H

#include "TexRect.h"
#include "AnimatedRect.h"

class Object {
public:
	bool isVisible;
	int ID;
	float X, Y, W, H;
	TexRect * Image;

	virtual void draw() = 0;
	virtual bool contains(const Object &) = 0;

	void XInc() { X += 0.01; }
	void XDec() { X -= 0.01; }
	void YInc() { Y += 0.01; }
	void YDec() { Y -= 0.01; }
	void Idle() {}
};

#endif // !OBJECT_H

