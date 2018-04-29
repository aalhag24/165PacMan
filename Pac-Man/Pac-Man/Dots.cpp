#include "stdafx.h"
#include "Dots.h"

Dots::Dots(float x, float y){
	X = x; Y = y;
	isVisible = true;
	float spacer = 0.01f;

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

bool Dots::contains(const float x, const float y) {
	if ((x + 0.01 < X && x - 0.01 > X) && (y + 0.01 > Y && y - 0.01 < Y)) { return true;  }
	else { return false; }
}