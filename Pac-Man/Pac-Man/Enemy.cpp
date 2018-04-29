#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Node *a) {
	X = a->CX; Y = a->CY;
	curr = a;
	Dir = 'U';
	isVisible = true;

	DIR = &Object::Idle;

	Image = new TexRect("Enemies.png",
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
}

Enemy::~Enemy() {
	delete Image;
}
