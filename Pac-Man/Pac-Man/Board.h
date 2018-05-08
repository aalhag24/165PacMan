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
#include "SDots.h"
#include "Enemy.h"

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
	TexRect * ScoreSign;
	TexRect * LiveSign;

	vector<Object*> Stash;
	Navigation * Field;

	Enemy *Uno, *Dos, *Tres;
	Player * PacMan;

	int Score, Lives;
	float Error;
	char Choice,NextDir;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();

	void SScreen();
	void GScreen();
	void PAScreen();

	void ExitGame();

	bool Aproximate(float, float);
	char Switch(char);

public:
	bool SelectionScreen, isMoving, 
		 GameStarted, Loss, 
		 Started = false, Won;

	Board();
	~Board();

	void draw();
	void Initialize();

	void Handle(float, float);
	void keyPressHandle(unsigned char);
	void specialKeyPressHandle(int);

	void Advance();
	void ChangePMDir();
	void ResetGame();
	void drawText(const char *text, int length, int x, int y);

	bool Reached();
	bool Collide();
	void Points();

	bool Availiable();
	bool Ready();
	bool Status();
	bool Winning();

};

#endif // !BOARD_H

