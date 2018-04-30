#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Node *a) {
	X = a->CX; Y = a->CY;
	curr = a;
	Dir = 'U';
	isVisible = true;

	Image = new AnimatedRect("Enemies.png", 1, 1, X, Y, 0.1f, 0.1f);
}

Enemy::~Enemy() {
	delete Image;
}
