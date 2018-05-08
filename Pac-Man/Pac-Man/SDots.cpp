#include "stdafx.h"
#include "SDots.h"

SDots::SDots(float x, float y, int i) {
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