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
	background = new TexRect("explode.bmp", "BackGround.bmp", 5, 5, 
		-(float)1.0, (float)0.8, (float)2.0, (float)1.8);
	painting = new TexRect("explode.bmp", "mushroom.bmp", 5, 5, 
		(float)0, (float)0.67, (float)0.5, (float)0.5);
	title = new TexRect("explode.bmp", "Title.bmp", 5, 5, 
		-(float)0.8, (float)0.8, (float)0.2, (float)1.6);
	StartGame = new TexRect("explode.bmp", "StartGame.png", 1, 1,
		-(float)0.8, (float)0.4, (float)0.2, (float)1.6);
	Exit = new TexRect("explode.bmp", "Exit.png", 1, 1,
		-(float)0.8, -(float)0.4, (float)0.2, (float)1.6);
	PlayAgain = new TexRect("explode.bmp", "PlayAgain.png", 1, 1,
		-(float)0.8, -(float)0.4, (float)0.2, (float)1.6);

	SelectionScreen = true;
	isMoving = false;
	GameStarted = false;
	Loss = false;
}

Board::~Board(){
	delete background;
	delete painting;

	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		delete (*it);
}

void Board::draw() {
	//painting->draw();
	if (Loss)
		PAScreen();
	else if(SelectionScreen)
		SScreen();
	else
		GScreen();
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
