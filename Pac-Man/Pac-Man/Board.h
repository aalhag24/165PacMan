#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"

#include "TexRect.h"
#include "Object.h"
#include "Dots.h"
#include "AnimatedRect.h"
#include "Player.h"
#include "Navigation.h"

#include <vector>

class Board {
	TexRect * painting;
	TexRect * background;
	TexRect * Title;
	TexRect * StartGame;
	TexRect * Exit;
	TexRect * PlayAgain;

	bool SelectionScreen, isMoving, GameStarted, Loss;
	int Score, Lives;

	vector<Object*> Stash;
	//Enemy *Uno, *Dos, *Tres;
	Player * PacMan;
	Navigation * Field;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();

	void SScreen();
	void GScreen();
	void PAScreen();

	void ExitGame();
	void ResetGame();

public:
	Board();
	~Board();

	void draw();

	void Handle(float, float);
	void keyPressHandle(unsigned char);
	void specialKeyPressHandle(int);

};

#endif // !BOARD_H

