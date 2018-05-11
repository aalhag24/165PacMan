#include "stdafx.h"
#include "SDots.h"

SDots::SDots(float x, float y, int i) : Object(x, y) {
	X = x; Y = y;
	isVisible = true;
	float spacer = 0.01f;

	Image = new AnimatedRect("PurpleDot.png", 1, 1, X - spacer, Y + spacer, 0.04f, 0.04f);
	id = i;
	//Image = new AnimatedRect("YellowDot.png", 1, 1, X, Y, 0.02f, 0.02f);

}

SDots::~SDots() {
	delete Image;
}

void SDots::draw() {
	Image->draw();
}

bool SDots::contains(const Parent *G){
	Object *P = (Object *)G;

	float l = sqrt(pow(P->X - X, 2) + pow(P->Y - Y, 2));
	if (l < P->W) { return true; }
	else { return false; }
}

bool SDots::contains(const float x, const float y){
	if ((x + 0.01 < X && x - 0.01 > X) && (y + 0.01 > Y && y - 0.01 < Y)) { return true; }
	else { return false; }
}
