#ifndef DOTS_H
#define DOTS_H

#include "TexRect.h"
#include "Object.h"
#include <cmath>

class Dots: public Object {
	//char* animation, * default_img;
public:
	Dots(int, float, float);
	~Dots();
	
	void draw();
	bool contains(const Object &G);
};

#endif // !DOTS_H

