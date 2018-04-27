#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y) {
	X = x; Y = y;

	Image = new TexRect("explode.bmp", "PacMan.png", 3, 1,
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
}

Player::~Player() {
	delete Image;
}

void Player::draw() {
	Image->draw();
}

bool Player::contains(const Object &G) {
	float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
	if (l < ((G.W + W) / 2)) { return true; }
	else { return false; }
}