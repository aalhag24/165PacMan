#ifndef ENEMY_H
#define ENEMY_H

#include "Navigation.h"
#include "Object.h"
#include "AnimatedRect.h"

class Enemy: public Navigation, public Object {
	Node * curr;
	Node * prev;

	char Dir;
public:
	Enemy(Node *);
	~Enemy();

	void draw();
	bool contains(const Object &);
};

#endif // !ENEMY_H

