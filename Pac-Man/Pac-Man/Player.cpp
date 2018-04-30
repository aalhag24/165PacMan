#include "stdafx.h"
#include "Player.h"

Player::Player(Node *a) {
	curr = a;
	Dir = 'L';
	isVisible = true;
	X = a->CX; Y = a->CY;

	Image = new AnimatedRect("PacMan2.png", 4, 5, X, Y, 0.1f, 0.1f);
	Image->decX(Image->getw()/2);
	Image->incY(Image->geth()/2);

	Image->DIR = &AnimatedRect::Idle;
	//DIR = &Idle;
}

Player::~Player() {
	//delete Image;
	delete curr;
	delete prev;
}