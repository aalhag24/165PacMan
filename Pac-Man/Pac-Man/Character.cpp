#include "stdafx.h"
#include "Character.h"

Character::Character(float x, float y) {
	X = x; Y = y;

	Image = new TexRect("explode.bmp", "YellowDot.png", 5, 5,
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
}

Character::~Character() {
	delete Image;
}

void Character::draw() {
	Image->draw();
}

bool Character::contains(const Object &G) {
	float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
	if (l < G.W) { return true; }
	else { return false; }
}
