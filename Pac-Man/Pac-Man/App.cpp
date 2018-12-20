#include "App.h"
#include "stdafx.h"
#include "Enemy.h"

static App* MF;

void app_timer(int value) {
	if (MF->MainFrame->Ready()) {
		//singleton->MainFrame.Title->animate();
		MF->MainFrame->Advance();
		MF->MainFrame->CheckEnemyDir();

		if (MF->MainFrame->Status()) {
			MF->MainFrame->ChangePMDir();
		}
		else if (MF->MainFrame->Reached()) {
			MF->MainFrame->ChangePMDir();
		}

		//Ememies and PacMan Collide
		if (MF->MainFrame->Collide()) {

		}
		if (MF->MainFrame->Winning()) {
			MF->MainFrame->Lossing(true);
		}

		//PacMan collision with dots gets points
		MF->MainFrame->Points(); 
	}

	MF->redraw();
	glutTimerFunc(32, app_timer, value);
}


App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	// Initialize state variables
	MF = this;

	mx = 0.0;
	my = 0.0;

	MainFrame = new Board();

	/**
	explode(0);
    glutTimerFunc(20, move, 1);
	**/

	app_timer(1);
}

void App::specialKeyPress(int key) {
	MainFrame->specialKeyPressHandle(key);
}

void App::specialKeyUp(int key) {}

void App::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3d(1.0, 1.0, 1.0);


	MainFrame->draw();

	glFlush();
	glutSwapBuffers();
}

void App::mouseDown(float x, float y) {
	mx = x;
	my = y;

	cout << mx << " " << my << endl;

	MainFrame->Handle(x, y);
	// Redraw the scene
	redraw();
}

void App::mouseDrag(float x, float y) {
	mx = x;
	my = y;

	// Redraw the scene
	redraw();
}

void App::idle() {
	redraw();
}

void App::keyPress(unsigned char key) {
	MainFrame->keyPressHandle(key);
}

