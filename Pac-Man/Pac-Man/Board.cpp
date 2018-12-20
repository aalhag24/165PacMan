#include "Board.h"
#include "stdafx.h"
#include "Enemy.h"
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
	Initialize();
	Initialize_PacMan();
	Initialize_Enemies();

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
	for (vector<Enemy*>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
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
// Initialize all objects
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
void Board::Initialize_PacMan() {
	PacMan = new Player(Field->StartNode);
	PacMan->Image->setPos(' ');
	PacMan->Image->animate();
}
void Board::Initialize_Enemies() {
	int i = 0;
	int A[] = { 66, 67, 68 };
	char D[] = { 'L', 'R', 'L' };
	for (vector<Enemy*>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it) {
		EnemyList.push_back(new Enemy(Field->List[A[i]], D[i]));
		EnemyList[i]->Image->animate();
		EnemyList[i]->setRow(i + 1);
		EnemyList[i]->Image->setPos(D[i]);
		EnemyList[i]->Image->pause();
		i++;
	}
}

// Handle Events
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
		EnemyList.clear();
		delete Field;
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
			// Sets the Initial Dir
			if (PacMan->next == nullptr && PacMan->setChoice(Choice)) {
				ChangePMDir();
			}
			// Checks if the prev dir is the one we switch to
			else if (PacMan->getChoice(Choice)) {
				ChangePMDir();
			}
		}
	}
}

// Draw Screens
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

	for (vector<Enemy*>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it)
		(*it)->draw();
	
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

// Exit parameters
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

// Reset all objects
void Board::Reset_Enemies() {
	for (vector<Enemy*>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it) {
		(*it)->Reset();
	}
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

void Board::Points() {
	float diff;
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it) {
		if ((*it)->isVisible) {
			diff = sqrt(pow(PacMan->Image->getx() - (*it)->X, 2) + pow(PacMan->Image->gety() - (*it)->Y, 2));
			if (diff < 4 * (PacMan->Image->getw() / 5)) {
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

/// Game Handle - I.e. colllision, points 
void Board::Advance(){
	PacMan->Image->advance();
	PacMan->Image->Shift(PacMan->Dir);
	for(vector<Enemy*>::iterator it = EnemyList.begin(); it!=EnemyList.end(); ++it){
		(*it)->Image->advance();
		(*it)->Image->Shift((*it)->Dir);
	}
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
			delete PacMan->prev;
			PacMan->prev = new Node(PacMan->next->ID, PacMan->next->CX, PacMan->next->CY, PacMan->next->Adj);
			Node *tmp = nullptr;

			tmp = new Node(PacMan->next->getNext(NextDir)->ID,
				PacMan->next->getNext(NextDir)->CX,
				PacMan->next->getNext(NextDir)->CY,
				PacMan->next->getNext(NextDir)->Adj);

			delete PacMan->next;
			PacMan->next = new Node(tmp->ID, tmp->CX, tmp->CY, tmp->Adj);
			delete tmp;
		}
		
		NextDir = ' ';
	}
	else {
		PacMan->Image->pause();
		PacMan->Dir = ' ';
		PacMan->Image->setPos(' ');
	}
}
void Board::CheckEnemyDir() {
	Node *tmp;
	for (vector<Enemy*>::iterator it = EnemyList.begin(); it != EnemyList.end(); ++it) {
		if (Reached((*it))) {
			if ((*it)->next == nullptr) {
				tmp = (*it)->next->PickRandNeighbor();
				(*it)->next = tmp;
			}
			else {
				(*it)->prev = (*it)->next;
				tmp = (*it)->next->PickRandNeighbor();
				(*it)->next = tmp;
			}
			/// Change the enemy pos here
			char D = (*it)->prev->NodeDirection((*it)->next);
			(*it)->Image->setPos(D);
			(*it)->Dir = D;

			//(*it)->Image->setx((*it)->next->CX);
			//(*it)->Image->sety((*it)->next->CY);
			//PacMan->Image->decX(PacMan->Image->getw() / 2);
			//PacMan->Image->incY(PacMan->Image->geth() / 2);
		}
	}
}
bool Board::Reached(){
	return(Aproximate(PacMan->next->CX, PacMan->Image->getx() + (PacMan->Image->getw() / 2)) &&
		   Aproximate(PacMan->next->CY, PacMan->Image->gety() - (PacMan->Image->geth() / 2)));
}
bool Board::Reached(Enemy * a) {
	return(Aproximate(a->next->CX, a->Image->getx() + (a->Image->getw() / 2)) &&
		   Aproximate(a->next->CY, a->Image->gety() - (a->Image->geth() / 2)));
}

bool Board::Collide(){

	/// Complete This

	return false;
}

bool Board::Aproximate(float a, float b){
	// a is the position we want to be at
	// b is current position
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
void Board::Lossing(bool a){
	Loss = a;
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