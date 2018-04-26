#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"
#include "TexRect.h"

class Board {
	TexRect * painting;
	TexRect * background;
	TexRect * title;

	bool SelectionScreen, isMoving, GameStarted;

	int Score, Lives;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();
public:
	Board();
	~Board();

	void draw();

	void Handle(float, float);
	void keyPressHandle(unsigned char);

	void SScreen();
	void GScreen();
};

#endif // !BOARD_H

