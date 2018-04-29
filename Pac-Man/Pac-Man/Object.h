#ifndef OBJECT_H
#define OBJECT_H

#include "TexRect.h"
#include "AnimatedRect.h"

class Object {
public:
	bool isVisible;
	static int ID;
	float X, Y, W, H;
	TexRect * Image;

	void draw() {
		Image->draw();
	}

	bool contains(const Object &G) {
		float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
		if (l < ((G.W + W) / 2)) { return true; }
		else { return false; }
	}

	bool contains(const float x, const float y) {
		float radius = 0.05;
		if ((x + radius > X && x - radius < X) && (y + radius > Y && y - radius < Y)) { return true; }
		else { return false; }
	}

	void XInc() { X += 0.01f; }
	void XDec() { X -= 0.01f; }
	void YInc() { Y += 0.01f; }
	void YDec() { Y -= 0.01f; }
	void Idle() {}
};

int Object::ID=0;

#endif // !OBJECT_H

