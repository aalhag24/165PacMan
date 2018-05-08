#ifndef ENEMY_H
#define ENEMY_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Enemy: public Navigation, public Object {
	Node * next;
	Node * prev;

	char Dir;
public:
	Enemy(Node *);
	~Enemy();

	bool getChoice(char);
	bool NextChoice(char);
	bool setChoice(char);

	void setRow(int);
};

#endif // !ENEMY_H

