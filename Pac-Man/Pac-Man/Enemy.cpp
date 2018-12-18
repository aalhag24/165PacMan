#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(Node *a, char d) {
	prev = a;
	next = nullptr;
	Dir = 'L';
	isVisible = true;
	X = a->CX; Y = a->CY;

	Origin = a;
	ODir = Dir;

	Image = new AnimatedRect("Enemies.bmp", 12, 12, X, Y, 0.1f, 0.1f);
	Image->decX(Image->getw() / 2);
	Image->incY(Image->geth() / 2);


	//DIR = &Idle;
}


Enemy::~Enemy() {
	//delete Image;
	delete next;
	delete prev;
}

bool Enemy::getChoice(char D) {
	if (next->NodeDirection(prev) == D) {
		return true;
	}
	return false;
}

// Finds if the next Choice is a valid one
bool Enemy::NextChoice(char D) {
	for (vector<Node*>::iterator it = next->Adj.begin(); it != next->Adj.end(); ++it) {
		if (next->NodeDirection(*it) == D) {
			return true;
		}
	}
	return false;
}

// Sets the Initial Choice when the game starts
bool Enemy::setChoice(char D) {
	for (vector<Node*>::iterator it = prev->Adj.begin(); it != prev->Adj.end(); ++it) {
		if (prev->NodeDirection(*it) == D) {
			return true;
		}
	}
	return false;
}

void Enemy::setRow(int a){
	Image->setRow(a);
}

void Enemy::Reset(){
	next=Origin;
	prev=NULL;
	Dir = ODir;
}
