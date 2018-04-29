#ifndef PLAYER_H
#define PLAYER_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Player : public Navigation, public Object{
	Node * curr;
	Node * prev;
public:
	char Dir;

	Player(Node *);
	~Player();
};

#endif // !PLAYER_H
