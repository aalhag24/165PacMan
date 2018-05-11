#ifndef OBJECT_H
#define OBJECT_H

#include "TexRect.h"
#include "AnimatedRect.h"
#include "Parent.h"
#include "Node.h"

class Object: public Parent {
public:
	bool isVisible;
	static int ID;
	int id;
	float X, Y, W, H;
	AnimatedRect *Image;

	Object(float x, float y) : X(x), Y(y) {}
	Object(Node *) {} 
	virtual ~Object()=0;

	void draw() {
		Image->draw();
	}

	bool contains(const Parent *G) {
		Object *P = (Object *)G;

		float l = sqrt(pow(P->X - X, 2) + pow(P->Y - Y, 2));
		if (l < P->W) { return true; }
		else { return false; }
	}

	bool contains(const float x, const float y) {
		float radius = 0.04f;
		return x - radius <= X && x + radius >= X && y - radius <= Y && y + radius >= Y;
	}
};

int Object::ID=0;

#endif // !OBJECT_H

