#ifndef DOTS_H
#define DOTS_H

#include "TexRect.h"
#include "Object.h"
#include <cmath>

class Dots: public Object {
	//char* animation, * default_img;
public:
	Dots(float, float,int);
	~Dots();
	
	void draw();
};

#endif // !DOTS_H

