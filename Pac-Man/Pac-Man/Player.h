#ifndef PLAYER_H
#define PLAYER_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Player : public Navigation, public Object{
public:
	Node * next;
	Node * prev;
	Node * Origin;
	char Dir;
	AnimatedRect * Images;

	Player(Node*);
	~Player();

	bool getChoice(char);
	bool NextChoice(char);
	bool setChoice(char);
	
	void Reset();
};

#endif // !PLAYER_H
