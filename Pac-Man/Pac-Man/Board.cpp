#include "Board.h"
#include "stdafx.h"

void Board::Reset_Enemies(){
}

void Board::Reset_Dots(){
	Stash.push_back(new Dots(0, 0));
}

void Board::Reset_PacMan(){
}

Board::Board(){
	background = new TexRect("BackGround.bmp", -1.0f, 0.8f, 2.0f, 1.8f);
	painting = new TexRect("mushroom.bmp",0.0f, 0.67f, 0.5f, 0.5f);

	PlayAgain = new TexRect("PlayAgain.png",-0.8f, -0.4f, 1.6f, 0.4f);

	Title = new TexRect("Title2.png", -0.8f, 1.0f, 1.7f, 0.6f);
	StartGame = new TexRect("StartGame.png", -0.65f, 0.4f, 1.2f, 0.4f);
	Exit = new TexRect("Exit1.png", -0.6f, -0.5f, 1.1f, 0.35f);

	Field = new Navigation();
	PacMan = new Player(Field->StartNode);

	SelectionScreen = true;
	isMoving = false;
	GameStarted = false;
	Loss = false;
}

Board::~Board(){
	delete background;
	delete painting;
	delete Title;
	delete StartGame;
	delete Exit;
	delete PlayAgain;

	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		delete (*it);
}

void Board::draw() {
	if (Loss)
		PAScreen();
	else if(SelectionScreen)
		SScreen();
	else
		GScreen();

}

void Board::Handle(float x, float y){
	if (Loss) {
		if (PlayAgain->contains(x, y))
			ResetGame();
	}
	else if (SelectionScreen) {
		if (StartGame->contains(x, y))
			SelectionScreen = false;
		if (Exit->contains(x, y))
			ExitGame();
	}
	else {
		// What does clicking do in game
	}

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
}

void Board::specialKeyPressHandle(int key){
	/// THIS SHOULD BE ALL THAT MATTERS
	if (!SelectionScreen) {
		if (key == 100) {
			PacMan->Dir = 'L'; //left = true;
		}
		if (key == 101) {
			PacMan->Dir = 'U'; //up = true;
		}
		if (key == 102) {
			PacMan->Dir = 'R'; //right = true;
		}
		if (key == 103) {
			PacMan->Dir = 'D'; //down = true;
		}
	}
}

void Board::SScreen(){
	Title->draw();
	StartGame->draw();
	Exit->draw();
}

void Board::GScreen(){
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		(*it)->draw();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POINTS);
	glVertex2f(0.0, 0.13);
	glVertex2f(0.0, -0.57);

	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.53, 0.7);
	glVertex2f(-0.53, 0.48);
	glVertex2f(-0.53, -0.05);
	glVertex2f(-0.53, 0.305);
	glVertex2f(-0.53, -0.39);
	glVertex2f(-0.53, -0.57);
	glVertex2f(-0.52, -0.75);

	glVertex2f(0.53, 0.7);
	glVertex2f(0.53, 0.48);
	glVertex2f(0.53, 0.305);
	glVertex2f(0.53, -0.05);
	glVertex2f(0.53, -0.39);
	glVertex2f(0.52, -0.57);
	glVertex2f(0.52, -0.75);

	glColor3d(0.0, 1.0, 1.0);
	glVertex2f(-0.88, 0.7);
	glVertex2f(-0.88, 0.48);
	glVertex2f(-0.88, 0.305);
	glVertex2f(-0.88, -0.39);
	glVertex2f(-0.88, -0.57);
	glVertex2f(-0.88, -0.75);
	glVertex2f(-0.88, -0.915);

	glVertex2f(0.88, 0.7);
	glVertex2f(0.88, 0.48);
	glVertex2f(0.88, 0.305);
	glVertex2f(0.88, -0.39);
	glVertex2f(0.88, -0.57);
	glVertex2f(0.88, -0.75);
	glVertex2f(0.88, -0.915);

	glColor3d(0.0, 0.0, 1.0);
	glVertex2f(0.74, -0.57);
	glVertex2f(0.74, -0.75);

	glVertex2f(-0.74, -0.57);
	glVertex2f(-0.74, -0.75);

	glColor3d(0.0, 1.0, 0.0);
	glVertex2f(-0.32, 0.48);
	glVertex2f(-0.32, 0.305);
	glVertex2f(-0.32, 0.125);
	glVertex2f(-0.32, -0.05);
	glVertex2f(-0.32, -0.24);
	glVertex2f(-0.32, -0.39);
	glVertex2f(-0.32, -0.57);
	glVertex2f(-0.32, -0.75);

	glVertex2f(0.32, 0.48);
	glVertex2f(0.32, 0.305);
	glVertex2f(0.32, 0.125);
	glVertex2f(0.32, -0.05);
	glVertex2f(0.32, -0.24);
	glVertex2f(0.32, -0.39);
	glVertex2f(0.32, -0.57);
	glVertex2f(0.32, -0.75);

	glColor3d(1.0, 0.0, 1.0);
	glVertex2f(-0.1, 0.7);
	glVertex2f(-0.1, 0.48);
	glVertex2f(-0.1, 0.305);
	glVertex2f(-0.1, 0.125);
	glVertex2f(-0.1, -0.39);
	glVertex2f(-0.1, -0.57);
	glVertex2f(-0.1, -0.75);
	glVertex2f(-0.1, -0.915);

	glVertex2f(0.1, 0.7);
	glVertex2f(0.1, 0.48);
	glVertex2f(0.1, 0.305);
	glVertex2f(0.1, 0.125);
	glVertex2f(0.1, -0.39);
	glVertex2f(0.1, -0.57);
	glVertex2f(0.1, -0.75);
	glVertex2f(0.1, -0.915);

	glEnd();

	background->draw();
}

void Board::PAScreen() {
	PlayAgain->draw();
	Exit->draw();
}

void Board::ExitGame(){

}

void Board::ResetGame(){
}
