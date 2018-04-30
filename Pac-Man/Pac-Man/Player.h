#ifndef PLAYER_H
#define PLAYER_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Player : public Navigation, public Object{
public:
	Node * curr;
	Node * prev;
	char Dir;
	AnimatedRect * Images;

	Player(Node *);
	~Player();
};

#endif // !PLAYER_H
