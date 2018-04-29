#include "stdafx.h"
#include "Dots.h"

Dots::Dots(int i, float x, float y){
	X = x; Y = y;
	isVisible = true;
	ID = i;
	float spacer = 0.01;

	Image = new TexRect("YellowDot.png", X-spacer, Y+spacer, (float)0.02, (float)0.02);
}

Dots::~Dots() {
	delete Image;
}

void Dots::draw(){
	Image->draw();
}

bool Dots::contains(const Object &G){
	float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
	if (l < G.W) { return true; }
	else { return false; }
}
