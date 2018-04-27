#ifndef PLAYER_H
#define PLAYER_H

#include "Navigation.h"
#include "Object.h"

class Player : public Navigation, public Object{
public:
	Player(float, float);
	~Player();

	void draw();
	bool contains(const Object &);
};

#endif // !PLAYER_H
