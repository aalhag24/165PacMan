#ifndef SDOTS_H
#define SDOTS_H

#include "TexRect.h"
#include "Object.h"
#include <cmath>

class SDots : public Object {
	//char* animation, * default_img;
public:
	SDots(float, float,int);
	~SDots();

	void draw();
};

#endif // !SDOTS_H

