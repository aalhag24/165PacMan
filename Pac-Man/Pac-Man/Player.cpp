#include "stdafx.h"
#include "Player.h"

Player::Player(Node *a) {
	X = a->CX; Y = a->CY;
	curr = a;
	Dir = 'L';

	DIR = &Navigation::Idle;

	Image = new TexRect("PacMan.png",
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
}

Player::~Player() {
	delete Image;
	delete curr;
	delete prev;
}

void Player::draw() {
	Image->draw();
}

bool Player::contains(const Object &G) {
	float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
	if (l < ((G.W + W) / 2)) { return true; }
	else { return false; }
}