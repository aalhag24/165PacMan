#include "Dots.h"

Dots::Dots(float x, float y){
	X = x; Y = y;

	Image = new TexRect("explode.bmp", "YellowDot.png", 5, 5, 
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
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
