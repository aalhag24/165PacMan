#ifndef ENEMY_H
#define ENEMY_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Enemy: public Navigation, public Object {
public:
	Node * next;
	Node * prev;
	Node * Origin;

	char Dir;
	char ODir;

	Enemy(Node *, char);
	~Enemy();

	bool getChoice(char);
	bool NextChoice(char);
	bool setChoice(char);

	void setRow(int);
	void Reset();
};

#endif // !ENEMY_H

