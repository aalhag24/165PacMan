#ifndef PLAYER_H
#define PLAYER_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Player : public Navigation, public Object{
	Node * curr;
	Node * prev;

	char Dir;
public:
	Player(Node *);
	~Player();

	void draw();
	bool contains(const Object &);
};

#endif // !PLAYER_H
