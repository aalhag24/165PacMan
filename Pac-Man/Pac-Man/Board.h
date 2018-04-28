#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"
#include "TexRect.h"
#include "Object.h"
#include "Dots.h"
#include <vector>
#include "AnimatedRect.h"

class Board {
public:
	TexRect * painting;
	TexRect * background;
	TexRect * Title;
	TexRect * StartGame;
	TexRect * Exit;
	TexRect * PlayAgain;

	//Navigation Field;

	int Score, Lives;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();

	vector<Object*> Stash;

	bool SelectionScreen, isMoving, GameStarted, Loss;

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

