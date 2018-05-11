#include "stdafx.h"
#include "Dots.h"

Dots::Dots(float x, float y, int i): Object (x,y){
	X = x; Y = y;
	isVisible = true;
	float spacer = 0.01f;

	Image = new AnimatedRect("YellowDot.png", 1, 1, X - spacer, Y + spacer, 0.02f, 0.02f);
	id = i;
	//Image = new AnimatedRect("YellowDot.png", 1, 1, X, Y, 0.02f, 0.02f);

}

Dots::~Dots() {
	delete Image;
}

void Dots::draw(){
	Image->draw();
}


bool Dots::contains(const Parent *G){
	Object *P = (Object *)G;

	float l = sqrt(pow(P->X - X, 2) + pow(P->Y - Y, 2));
	if (l < P->W) { return true; }
	else { return false; }
}

bool Dots::contains(const float x, const float y) {
	if ((x + 0.01 < X && x - 0.01 > X) && (y + 0.01 > Y && y - 0.01 < Y)) { return true;  }
	else { return false; }
}
