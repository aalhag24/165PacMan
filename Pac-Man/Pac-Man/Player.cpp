#include "stdafx.h"
#include "Player.h"

Player::Player(Node *a) {
	prev = a;
	next = nullptr;
	Dir = 'L';
	isVisible = true;
	X = a->CX; Y = a->CY;

	Image = new AnimatedRect("PacMan2.png", 4, 5, X, Y, 0.1f, 0.1f);
	Image->decX(Image->getw()/2);
	Image->incY(Image->geth()/2);


	//DIR = &Idle;
}

Player::~Player() {
	//delete Image;
	delete next;
	delete prev;
}

bool Player::getChoice(char D){
	if (next->NodeDirection(prev) == D) {
		return true;
	}
	return false;
}

// Finds if the next Choice is valid
bool Player::NextChoice(char D){
	for (vector<Node*>::iterator it = next->Adj.begin(); it != next->Adj.end(); ++it) {
		if (next->NodeDirection(*it) == D) {
			return true;
		}
	}
	return false;
}

// Sets the Initial Choice when the game starts
bool Player::setChoice(char D) {
	for (vector<Node*>::iterator it = prev->Adj.begin(); it != prev->Adj.end(); ++it) {
		if (prev->NodeDirection(*it) == D) {
			return true;
		}
	}
	return false;
}

// Reset the player to the start
void Player::Reset() {
	next=Origin;
	prev=NULL;
}
