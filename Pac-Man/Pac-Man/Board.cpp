#include "Board.h"
#include "stdafx.h"

void Board::Reset_Enemies(){

}

void Board::Reset_Dots(){
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		(*it)->isVisible = true;
}

void Board::Reset_PacMan(){
	PacMan->X = Field->List[0]->CX;
	PacMan->Y = Field->List[0]->CY;
	PacMan->curr = Field->List[0];
	PacMan->prev = NULL;
	PacMan->Dir = 'L';
	PacMan->Image->setPos(PacMan->Dir);
	PacMan->isVisible = true;
	PacMan->Image->reset();
}

Board::Board(){
	background = new TexRect("BackGround.bmp", -1.0f, 0.8f, 2.0f, 1.8f);
	painting = new TexRect("mushroom.bmp",0.0f, 0.67f, 0.5f, 0.5f);

	PlayAgain = new TexRect("PlayAgain.png",-0.8f, -0.4f, 1.6f, 0.4f);
	Loading = new TexRect("Loading.png", -0.8f, -0.4f, 1.6f, 0.4f);

	Title = new TexRect("Title2.png", -0.8f, 1.0f, 1.7f, 0.6f);
	StartGame = new TexRect("StartGame.png", -0.65f, 0.4f, 1.2f, 0.4f);
	Exit = new TexRect("Exit1.png", -0.6f, -0.5f, 1.1f, 0.35f);

	Field = new Navigation();
	Field->Initialize();
	PacMan = new Player(Field->StartNode);
	PacMan->Image->setPos(PacMan->Dir);
	PacMan->Image->animate();
	Initialize();

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
	delete Loading;

	delete PacMan;
	delete Field;

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

void Board::Initialize(){
	ifstream inFile;
	int Num, ID; float XVal, YVal, pos = 0;
	ifstream myfile("DotsList.txt", ios::out | ios::binary);

	if (!myfile.is_open()) {
		cout << "Unable to open file";
		exit(1);
	}
	ID = 0;
	cout << "Here" << endl;
	while (myfile.is_open()) {
		myfile >> Num >> XVal;
		if (Num == 101)
			break;
		for (int i = 0; i < Num; i++) {
			myfile >> YVal;
			Object *p = new Dots(XVal, YVal);
			Stash.push_back(p);
			cout << "Dot " << ID << endl;
			ID++;
		}
	}
	inFile.close();
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
		cout << "Here" << endl;
		for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it) {
			if ((*it)->contains(x, y)) {
				cout << "dot: " << (*it)->X << " " << (*it)->Y << endl;
				(*it)->isVisible = false;
			}
		}
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
		PacMan->Image->setPos(PacMan->Dir);
	}
}

void Board::SScreen(){
	Title->draw();
	StartGame->draw();
	Exit->draw();
}

void Board::GScreen(){
	//background->draw();
	PacMan->draw();

	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		if((*it)->isVisible)
			(*it)->draw();

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
