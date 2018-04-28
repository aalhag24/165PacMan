#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Node *a) {
	X = a->CX; Y = a->CY;
	curr = a;
	Dir = 'U';

	Image = new TexRect("Enemies.png",
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
}

Enemy::~Enemy() {
	delete Image;
}

void Enemy::draw() {
	Image->draw();
}

bool Enemy::contains(const Object &G) {
	float l = sqrt(pow(G.X - X, 2) + pow(G.Y - Y, 2));
	if (l < ((G.W + W)/2)) { return true; }
	else { return false; }
}