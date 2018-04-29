#include "stdafx.h"
#include "Player.h"

Player::Player(Node *a) {
//	X = a->CX; Y = a->CY;
	curr = a;
	Dir = 'L';
	isVisible = true;

	DIR = &Object::Idle;

	Image = new TexRect("PacMan.png",
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
}

Player::~Player() {
	delete Image;
	delete curr;
	delete prev;
}