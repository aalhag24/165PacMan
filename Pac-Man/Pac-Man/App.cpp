#include "App.h"
#include "stdafx.h"

static App* MF;

void app_timer(int value) {
	if (!MF->MainFrame->SelectionScreen && !MF->MainFrame->Loss) {
		//singleton->MainFrame.Title->animate();
		MF->MainFrame->Advance(); //MF->MainFrame->PacMan->Image->advance();
		if (MF->MainFrame->Reached()) {
			MF->MainFrame->ChangePMDir();
			MF->MainFrame->Move();
		}
		if (MF->MainFrame->Collide()) { //Ememies and PacMan Collide

		}
		if (MF->MainFrame->Points()) { //PacMan collision with dots gets points

		}
	}
	if (MF->MainFrame->Loss) {

	}
	MF->redraw();
	glutTimerFunc(100, app_timer, value);
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

	//app_timer(1);
}

void App::specialKeyPress(int key) {
	MainFrame->specialKeyPressHandle(key);
/**
	if (!game_over) {
		if (key == 100) {
			left = true;
		}
		if (key == 101) {
			//up = true;
		}
		if (key == 102) {
			right = true;
		}
		if (key == 103) {
			//down = true;
		}
	}
**/
}

void App::specialKeyUp(int key) {
/**
	if (key == 100) {
		left = false;
	}
	if (key == 101) {
		up = false;
	}
	if (key == 102) {
		right = false;
	}
	if (key == 103) {
		down = false;
	}

**/
}

void App::draw() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	glClear(GL_COLOR_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Color
	glColor3d(1.0, 1.0, 1.0);


	MainFrame->draw();

	//glDisable(GL_TEXTURE_2D);

	glFlush();
	glutSwapBuffers();

}

void App::mouseDown(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	cout << mx << " " << my << endl;

	MainFrame->Handle(x, y);
	// Redraw the scene
	redraw();
}

void App::mouseDrag(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	// Redraw the scene
	redraw();
}

void App::idle() {
	//    painting->advance();
	redraw();
}

void App::keyPress(unsigned char key) {
	MainFrame->keyPressHandle(key);
}

