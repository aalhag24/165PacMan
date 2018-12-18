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
	vector<Enemy*> EnemyList;

	Navigation * Field;
	Player * PacMan;

	int Score, Lives;
	float Error;
	char Choice,NextDir;
	bool SelectionScreen, isMoving,
		GameStarted, Loss, Started, Won;

	void Reset_Enemies();
	void Reset_Dots();
	void Reset_PacMan();

	void Initialize_Enemies();
	void Initialize_PacMan();

	void SScreen();
	void GScreen();
	void PAScreen();
	void ExitGame();

	void Initialize();
	void drawText(const char *text, int length, int x, int y);

	bool Aproximate(float, float);
	bool Reached(Enemy *);
	char Switch(char);

public:

	Board();
	~Board();

	void draw();

	void Handle(float, float);
	void keyPressHandle(unsigned char);
	void specialKeyPressHandle(int);

	void Advance();
	void ChangePMDir();
	void ResetGame();
	void Points();

	void CheckEnamyDir();

	bool Reached();
	bool Collide();

	bool Availiable();
	bool Ready();
	bool Status();
	bool Winning();
	void Lossing(bool);
};

#endif // !BOARD_H

