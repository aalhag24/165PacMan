#include "Board.h"
#include "stdafx.h"

void Board::Reset_Enemies(){
}

void Board::Reset_Dots(){
}

void Board::Reset_PacMan(){
}

Board::Board(){
	background = new TexRect("explode.bmp", "BackGround.bmp", 5, 5, -(float)1.0, (float)0.8, (float)2.0, (float)1.8);
	painting = new TexRect("explode.bmp", "mushroom.bmp", 5, 5, (float)0, (float)0.67, (float)0.5, (float)0.5);
	title = new TexRect("explode.bmp", "Title.bmp", 5, 5, -(float)0.8, (float)0.8, (float)0.2, (float)1.6);

	SelectionScreen = true;
	isMoving = false;
	GameStarted = false;
}

Board::~Board(){
	delete background;
	delete painting;
}

void Board::draw() {
	//painting->draw();
	if (SelectionScreen)
		SScreen();
	else
		GScreen();
}

void Board::Handle(float x, float y){
/**
	if(painting->contains(mx, my) && !painting->ani_toggle){
		painting->toggle();
		painting->reset();
		explode(0);
	}
**/
}

void Board::keyPressHandle(unsigned char key) {
	if (key == 27) {			// Exit the app when Esc key is pressed
		delete painting;		//delete background;
		exit(0);
	}
	else if (key == ' ') {
		painting->reset();
		painting->toggleReset();
		//redraw();
	}
	else if (key == '1') {
		painting->toggleReset();
	}
}

void Board::SScreen(){
	title->draw();

	glColor3f(1.0, 0.0, 1.0);

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 1.0);
	glVertex2f(0.0, -1.0);
	glEnd();

	//First I - One Player
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.7, 0.5);
	glVertex2f(-0.2, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.7, -0.5);
	glVertex2f(-0.2, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.45, 0.5);
	glVertex2f(-0.45, -0.5);
	glEnd();

	//Second II - Two Players
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.7, 0.5);
	glVertex2f(0.2, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.7, -0.5);
	glVertex2f(0.2, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.3, 0.5);
	glVertex2f(0.3, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(0.6, 0.5);
	glVertex2f(0.6, -0.5);
	glEnd();

}

void Board::GScreen(){
	background->draw();
}
