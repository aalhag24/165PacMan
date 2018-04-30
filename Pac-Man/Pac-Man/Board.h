#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"

#include "TexRect.h"
#include "Object.h"
#include "Dots.h"
#include "AnimatedRect.h"
#include "Player.h"
#include "Navigation.h"
#include "App.h"

#include <vector>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class Board {
	TexRect * painting;
	TexRect * background;
	TexRect * Title;
	TexRect * StartGame;
	TexRect * Exit;
	TexRect * PlayAgain;
	TexRect * Loading;

	vector<Object*> Stash;
	Navigation * Field;

	//Enemy *Uno, *Dos, *Tres;
	Player * PacMan;

	int Score, Lives;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();

	void SScreen();
	void GScreen();
	void PAScreen();

	void ExitGame();
	void ResetGame();

public:
	bool SelectionScreen, isMoving, GameStarted, Loss;

	Board();
	~Board();

	void draw();
	void Initialize();

	void Handle(float, float);
	void keyPressHandle(unsigned char);
	void specialKeyPressHandle(int);

	void Advance();
	void ChangePMDir();
	void Move();

	bool Reached();
	bool Collide();
	bool Points();
};

#endif // !BOARD_H

