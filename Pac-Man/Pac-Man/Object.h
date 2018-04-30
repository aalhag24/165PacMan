#ifndef OBJECT_H
#define OBJECT_H

#include "TexRect.h"
#include "AnimatedRect.h"

class Object {
public:
	bool isVisible;
	static int ID;
	float X, Y, W, H;
	AnimatedRect *Image;

	void draw() {
		Image->draw();
	}

	bool contains(const Object &G) {
		float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
		if (l < ((G.W + W) / 2)) { return true; }
		else { return false; }
	}

	bool contains(const float x, const float y) {
		float radius = 0.04f;
		return x - radius <= X && x + radius >= X && y - radius <= Y && y + radius >= Y;
	}
};

int Object::ID=0;

#endif // !OBJECT_H

