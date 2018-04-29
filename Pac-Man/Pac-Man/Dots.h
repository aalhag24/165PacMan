#ifndef DOTS_H
#define DOTS_H

#include "TexRect.h"
#include "Object.h"
#include <cmath>

class Dots: public Object {
	//char* animation, * default_img;
public:
	Dots(float, float);
	~Dots();
	
	void draw();
	bool contains(const Object &G);
	bool contains(const float, const float);
};

#endif // !DOTS_H

