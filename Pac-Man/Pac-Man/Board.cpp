#include "Board.h"
#include "stdafx.h"

Board::Board(){
	background = new TexRect("explode.bmp", "BackGround.bmp", 5, 5, -(float)1.0, (float)0.8, (float)2.0, (float)1.8);
	painting = new TexRect("explode.bmp", "mushroom.bmp", 5, 5, (float)0, (float)0.67, (float)0.5, (float)0.5);

	SelectionScreen = true;
}

Board::~Board(){
	delete background;
	delete painting;
}

void Board::draw() {
	painting->draw();
	background->draw();
}

void Board::handle(){
}

void Board::keyPressHandle(){
}
