#include "Board.h"
#include "stdafx.h"
#include <cassert>

Board::Board(){
	Started = false;
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
	PacMan->Image->setPos(' ');
	PacMan->Image->animate();
	Initialize();

	SelectionScreen = true;
	isMoving = false;
	GameStarted = false;
	Loss = false;
	Started = true;

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
	ifstream inFile;
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
			Object *p = new Dots(XVal, YVal);
			Stash.push_back(p);
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
		for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it) {
			if ((*it)->contains(x, y)) {
				//cout << "dot: " << (*it)->X << " " << (*it)->Y << endl;
				(*it)->isVisible = false;
			}
		}
	}
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

void Board::Reset_Enemies() {

}
void Board::Reset_Dots() {
	for (vector<Object*>::iterator it = Stash.begin(); it != Stash.end(); ++it)
		(*it)->isVisible = true;
}
void Board::Reset_PacMan() {
	PacMan->X = Field->List[0]->CX;
	PacMan->Y = Field->List[0]->CY;
	PacMan->prev = Field->List[0];
	PacMan->next = NULL;
	PacMan->Dir = ' ';
	PacMan->Image->setPos('L');
	PacMan->isVisible = true;
	PacMan->Image->reset();
}
void Board::ResetGame(){
	Reset_Dots();
	Reset_PacMan();
	Reset_Enemies();
}

void Board::swap(Node * a, Node * b){
	Node* c = a;
	a = b;
	b = c;
}

/// Game Handle - I.e. colllision, points 

void Board::Advance(){
	PacMan->Image->advance();
	PacMan->Image->Shift(PacMan->Dir);
}

void Board::ChangePMDir(){
	if (NextDir != ' ') {
		PacMan->Image->resume();
		PacMan->Image->setPos(NextDir);
		PacMan->Dir = NextDir;
		
		if(NextDir == ' ')
			cout <<  " NextDir == ' ' "<< endl;
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
			if(PacMan->next->getNext(NextDir) == nullptr)
				cout << "Issues" << endl;

			tmp = new Node(PacMan->next->getNext(NextDir)->ID,
				PacMan->next->getNext(NextDir)->CX,
				PacMan->next->getNext(NextDir)->CY,
				PacMan->next->getNext(NextDir)->Adj);

			delete PacMan->next;
			PacMan->next = new Node(tmp->ID, tmp->CX, tmp->CY, tmp->Adj);
			delete tmp;
		}
		

		cout << " asdfas :" << endl;
		cout << PacMan->next->CX << " " << PacMan->next->CY << endl;

		//Make this into a new player function
		PacMan->Image->setx(PacMan->next->CX);
		PacMan->Image->sety(PacMan->next->CY);
		//PacMan->Image->decX(PacMan->Image->getw() / 2);
		//PacMan->Image->incY(PacMan->Image->geth() / 2);
		NextDir = ' ';
	}
	else {
		PacMan->Image->pause();
		PacMan->Dir = NextDir;
		PacMan->Image->setPos(' ');
	}
}

bool Board::Reached(){
	cout << PacMan->next->CX << " VS " << PacMan->Image->getx() + (PacMan->Image->getw() / 2) << " AND " <<
			PacMan->next->CY << " VS " << PacMan->Image->gety() - (PacMan->Image->geth() / 2) << endl;
	return(Aproximate(PacMan->next->CX, PacMan->Image->getx() + (PacMan->Image->getw() / 2)) &&
		Aproximate(PacMan->next->CY, PacMan->Image->gety() - (PacMan->Image->geth() / 2)));
}

bool Board::Collide(){
	return false;
}

bool Board::Points(){
	return false;
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