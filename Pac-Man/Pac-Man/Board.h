#ifndef BOARD_H
#define BOARD_H

#include "stdafx.h"
#include "TexRect.h"

class Board {
private:
	TexRect * painting;
	TexRect * background;

	bool SelectionScreen;

public:
	Board();
	~Board();

	void draw();

	void handle();
	void keyPressHandle();
};

#endif // !BOARD_H

