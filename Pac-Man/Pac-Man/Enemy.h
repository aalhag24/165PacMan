#ifndef ENEMY_H
#define ENEMY_H

#include "Navigation.h"
#include "Object.h"

class Enemy: public Navigation, public Object {
public:
	Enemy(float, float);
	~Enemy();

	void draw();
	bool contains(const Object &);

};

#endif // !ENEMY_H

