#include "Board.h"
#include "stdafx.h"
#include <cassert>
#include <iostream>    
#include <iomanip> 
#include <sstream>
#include <string>

Board::Board(){
	background = new TexRect("BackGround.bmp", -1.0f, 0.8f, 2.0f, 1.8f);
	painting = new TexRect("mushroom.bmp",0.0f, 0.67f, 0.5f, 0.5f);

	PlayAgain = new TexRect("PlayAgain.png",-0.8f, -0.4f, 1.6f, 0.4f);
	Loading = new TexRect("Loading.png", -0.8f, -0.4f, 1.6f, 0.4f);
	ScoreSign = new TexRect("Score.bmp", -0.95f, 1.0f, 0.4f, 0.2f);
	LiveSign = new TexRect("Lives.bmp", 0.1f, 1.0f, 0.4f, 0.2f);

	Title = new TexRect("Title2.png", -0.8f, 1.0f, 1.7f, 0.6f);
	StartGame = new TexRect("StartGame.png", -0.65f, 0.4f, 1.2f, 0.4f);
	Exit = new TexRect("Exit1.png", -0.6f, -0.5f, 1.1f, 0.35f);


	Field = new Navigation();
	Field->Initialize();
	PacMan = new Player(Field->StartNode);
	PacMan->Image->setPos(' ');
	PacMan->Image->animate();
	Initialize();

	Uno = new Enemy(Field->List[66]);
		Uno->Image->animate();
		Uno->setRow(1);
		Uno->Image->setPos('L');
		Uno->Image->pause();

	Dos = new Enemy(Field->List[67]);
		Dos->Image->animate();
		Dos->setRow(2);
		Dos->Image->setPos('R');
		Dos->Image->pause();
	Tres = new Enemy(Field->List[68]);
		Tres->Image->animate();
		Tres->setRow(3);
		Tres->Image->setPos('L');
		Tres->Image->pause();

	SelectionScreen = true;
	isMoving = false;
	GameStarted = false;
	Loss = false;
	Started = true;
	Won = false;

	Score = 0;
	Lives = 1;

	Error = 0.01f;
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
	int Num, ID; float XVal, YVal, pos = 0;
	ifstream myfile("DotsList.txt", ios::out | ios::binary);

	if (!myfile.is_open()) {
		cout << "Unable to open file";
		exit(1);
	}
	ID = 0;

	while (myfile.is_open()) {
		myfile >> Num >> XVal;
		if (Num == 101)
			break;
		for (int i = 0; i < Num; i++) {
			myfile >> YVal;
			Object *p = new Dots(XVal, YVal, ID);
			Stash.push_back(p);
			ID++;
		}
	}
	myfile.close();

	ifstream myfile2("SDotsList.txt", ios::out | ios::binary);
	if (!myfile2.is_open()) {
		cout << "Unable to open file";
		exit(1);
	}
	while (myfile2.is_open()) {
		myfile2 >> Num >> XVal;
		if (Num == 101)
			break;
		for (int i = 0; i < Num; i++) {
			myfile2 >> YVal;
			Object *p = new SDots(XVal, YVal, ID);
			Stash.push_back(p);
			ID++;
		}
	}
	myfile2.close();

}
void Board::Handle(float x, float y){
	if (Loss) {
		if (PlayAgain->contains(x, y)) {
			ResetGame();
			SelectionScreen = true;
			Loss = false;
		}
	}
	else if (SelectionScreen) {
		if (StartGame->contains(x, y))
			SelectionScreen = false;
		if (Exit->contains(x, y))
			ExitGame();
	}
}
void Board::keyPressHandle(unsigned char key) {
	if (key == 27) {			// Exit the app when Esc key is pressed
		delete painting;
		delete background;
		delete Title;
		delete StartGame;
		delete Exit;
		delete PlayAgain;
		delete Loading;
		delete ScoreSign;
		delete LiveSign;

		Stash.clear();
		delete Field;

		delete Uno;
		delete Dos;
		delete Tres;
		delete PacMan;
		exit(0);
	}
}
void Board::specialKeyPressHandle(int key){
	/// THIS SHOULD BE ALL THAT MATTERS
	if (!SelectionScreen) {
		switch (key) {
			case 100: Choice = 'L'; break;
			case 101: Choice = 'U'; break;
			case 102: Choice = 'R'; break;
			case 103: Choice = 'D'; break;
			default:  Choice = ' '; break;
		}
		if (Choice != ' ') {
			NextDir = Choice;
			if (PacMan->next == nullptr && PacMan->setChoice(Choice)) { // Sets the Initial Dir
				ChangePMDir();
			}
			else if (PacMan->getChoice(Choice)) { // Checks if the prev dir is the one we switch to
				ChangePMDir();
			}
		}
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
	ScoreSign->draw();
	LiveSign->draw();

	Uno->draw();
	Dos->draw();
	Tres->draw();
	
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		if((*it)->isVisible)
			(*it)->draw();


	string text, Text;
	text = to_string(Score);
	int liv = 1;
	Text = to_string(liv);
	drawText(text.data(), text.size(), 140, 468);
	drawText(Text.data(), Text.size(), 400, 468);

	background->draw();
}
void Board::PAScreen() {
	PlayAgain->draw();
	Exit->draw();
}
void Board::ExitGame() {
	delete painting;
	delete background;
	delete Title;
	delete StartGame;
	delete Exit;
	delete PlayAgain;
	delete Loading;
	delete ScoreSign;
	delete LiveSign;

	Stash.clear();
	delete Field;

	//delete *Uno, *Dos, *Tres;
	delete PacMan;
	exit(0);
}

void Board::drawText(const char *text, int length, int x, int y) {
	glColor3d(1, 1, 1);
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(10, 500, 10, 500, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++){
		glutBitmapCharacter(font, text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);
}

void Board::Reset_Enemies() {

}
void Board::Reset_Dots() {
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		(*it)->isVisible = true;
}
void Board::Reset_PacMan() {
	PacMan->prev = Field->List[0];
	PacMan->Dir = ' ';
	PacMan->X = 0.0f;
	PacMan->Y = -0.57f;
	PacMan->Image->setx(PacMan->X);
	PacMan->Image->sety(PacMan->Y);
	PacMan->Image->decX(PacMan->Image->getw() / 2);
	PacMan->Image->incY(PacMan->Image->geth() / 2);

	cout << Field->List[0]->CX << " " << Field->List[0]->CY << endl;
	
	PacMan->Image->pause();
	PacMan->Image->setPos(' ');
}
void Board::ResetGame(){
	delete Field;
	Field = new Navigation();
	Field->Initialize();
	Reset_Dots();
	Reset_PacMan();
	//Reset_Enemies();

	SelectionScreen = true;
	isMoving = false;
	GameStarted = false;
	Loss = false;
	Started = true;
	Won = false;

	Score = 0;
	Lives = 1;
}


/// Game Handle - I.e. colllision, points 
void Board::Advance(){
	PacMan->Image->advance();
	PacMan->Image->Shift(PacMan->Dir);
	/*
	Uno->Image->advance();
	Uno->Image->Shift(PacMan->Dir);
	Dos->Image->advance();
	Dos->Image->Shift(PacMan->Dir);
	Tres->Image->advance();
	Tres->Image->Shift(PacMan->Dir);
	*/
}
void Board::ChangePMDir() {
	bool check = true;
	if (Lives < 0) {
		Loss = true;
	}
	if (PacMan->next != nullptr) {
		if (PacMan->next->getNext(NextDir) == nullptr) {
			check = false;
		}
	}
	if (NextDir != ' ' && check) {
		PacMan->Image->resume();
		PacMan->Image->setPos(NextDir);
		PacMan->Dir = NextDir;

		if(PacMan->next == nullptr){ 
			Node *tmp = new Node(PacMan->prev->getNext(NextDir)->ID, 
								 PacMan->prev->getNext(NextDir)->CX, 
								 PacMan->prev->getNext(NextDir)->CY,
								 PacMan->prev->getNext(NextDir)->Adj);
			delete PacMan->next;
			PacMan->next = new Node(tmp->ID, tmp->CX, tmp->CY, tmp->Adj);
 			delete tmp;
		}
		else {	
				/// Switch prev = next
			delete PacMan->prev;
			PacMan->prev = new Node(PacMan->next->ID, PacMan->next->CX, PacMan->next->CY, PacMan->next->Adj);

				/// Switch next to the next->next
			Node *tmp = nullptr;

			tmp = new Node(PacMan->next->getNext(NextDir)->ID,
				PacMan->next->getNext(NextDir)->CX,
				PacMan->next->getNext(NextDir)->CY,
				PacMan->next->getNext(NextDir)->Adj);

			delete PacMan->next;
			PacMan->next = new Node(tmp->ID, tmp->CX, tmp->CY, tmp->Adj);
			delete tmp;
		}
		

		// Make this into a new player function
		//PacMan->Image->setx(PacMan->next->CX);
		//PacMan->Image->sety(PacMan->next->CY);
		// PacMan->Image->decX(PacMan->Image->getw() / 2);
		// PacMan->Image->incY(PacMan->Image->geth() / 2);
		NextDir = ' ';
	}
	else {

		PacMan->Image->pause();
		PacMan->Dir = ' ';
		PacMan->Image->setPos(' ');
	}
}
bool Board::Reached(){
	return(Aproximate(PacMan->next->CX, PacMan->Image->getx() + (PacMan->Image->getw() / 2)) &&
		Aproximate(PacMan->next->CY, PacMan->Image->gety() - (PacMan->Image->geth() / 2)));
}
bool Board::Collide(){
	return false;
}
void Board::Points(){
	float diff;
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it) {
		if ((*it)->isVisible) {
			diff = sqrt(pow(PacMan->Image->getx() - (*it)->X, 2) + pow(PacMan->Image->gety() - (*it)->Y, 2));
			if (diff < 4*(PacMan->Image->getw()/5)) {
				(*it)->isVisible = false;
				if ((*it)->id >= 212) {
					Score += 100;
				}
				else {
					Score += 10;
				}
			}
		}
	}
	if (Score >= 2500) {
		cout << "Won" << endl;
		Won = true;
	}
}

bool Board::Aproximate(float a, float b){
	// a is the pos we want to be at
	// b is current pos
	return (b > a - Error && b < a + Error);
}
bool Board::Availiable() {
	return(PacMan->next != nullptr);
}
bool Board::Ready() {
	return (!SelectionScreen && !Loss && Availiable());
}
bool Board::Status() { 
	return (PacMan->next == nullptr); 
}
bool Board::Winning(){
	return Won;
}
char Board::Switch(char D) {
	switch (D) {
	case 'R': D = 'L'; break;
	case 'L': D = 'R'; break;
	case 'D': D = 'U'; break;
	case 'U': D = 'D'; break;
	default:   break;
	}
	return D;
}