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
	StartGame = new TexRect("StartGame.png", -0.82f, 0.4f, 1.62f, 0.4f);
	Exit = new TexRect("Exit1.png", -0.6f, -0.2f, 1.1f, 0.35f);


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
/**
	if (Loss)
		PAScreen();
	else if(SelectionScreen)
		SScreen();
	else
		GScreen();
*/
	SScreen();
}

void Board::Handle(float x, float y){
	if (Loss) {
		//if(x >)
	}
	else if (SelectionScreen) {}
	else {}

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
		//painting->reset();
		//painting->toggleReset();
		//redraw();
	}
	else if (key == '1') {
		//painting->toggleReset();
	}
}

void Board::SScreen(){
	Title->draw();
	StartGame->draw();
	Exit->draw();
}

void Board::GScreen(){
	background->draw();
	
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		(*it)->draw();
}

void Board::PAScreen() {
	PlayAgain->draw();
	Exit->draw();
}
