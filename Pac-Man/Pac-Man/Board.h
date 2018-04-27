#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"
#include "TexRect.h"
#include "Object.h"
#include "Dots.h"

class Board {
	TexRect * painting;
	TexRect * background;
	TexRect * title;
	TexRect * StartGame;
	TexRect * Exit;
	TexRect * PlayAgain;

	bool SelectionScreen, isMoving, GameStarted, Loss;

	int Score, Lives;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();

	vector<Object*> Stash;

public:
	Board();
	~Board();

	void draw();

	void Handle(float, float);
	void keyPressHandle(unsigned char);

	void SScreen();
	void GScreen();
	void PAScreen();
};

#endif // !BOARD_H

