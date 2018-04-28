#include "App.h"
#include "stdafx.h"

static App* singleton;

/**
void explode(int value){
	if (!singleton->painting->done()){
		singleton->painting->advance();
		singleton->redraw();
		glutTimerFunc(32, explode, value);
	}
}

void move(int value){
	if (singleton->isMoving){
		singleton->painting->incY();
		singleton->redraw();
		glutTimerFunc(32, move, value);
	}
}


void app_timer(int value) {
	if (singleton->MainFrame.SelectionScreen) {
		singleton->MainFrame.Title->animate();
		glutTimerFunc(100, app_timer, value);
	}

	if (singleton->moving) {
		singleton->ball->jump();
		float bx = singleton->ball->x + singleton->ball->w / 2;
		float by = singleton->ball->y - singleton->ball->h + 0.1;
		if (singleton->platform->contains(bx, by)) {
			singleton->ball->rising = true;
			singleton->ball->yinc += 0.005;
			singleton->ball->xinc = singleton->ball->yinc;
			if (singleton->ball->yinc > 0.15) {
				singleton->ball->yinc = 0.15;
			}
		}

		if (singleton->ball->y - singleton->ball->h < -0.99) {
			singleton->moving = false;
			singleton->game_over = true;
			singleton->gameOver->animate();

		}
	}
	if (singleton->up) {
		singleton->platform->moveUp(0.05);
	}
	if (singleton->down) {
		singleton->platform->moveDown(0.05);
	}
	if (singleton->left) {
		singleton->platform->moveLeft(0.05);
	}
	if (singleton->right) {
		singleton->platform->moveRight(0.05);
	}

	if (singleton->game_over) {
		singleton->redraw();
		glutTimerFunc(100, app_timer, value);
	}
	else {
		if (singleton->up || singleton->down || singleton->left || singleton->right || singleton->moving && !singleton->game_over) {
			singleton->redraw();
			glutTimerFunc(16, app_timer, value);
		}
	}

}
*/


App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	// Initialize state variables
	singleton = this;

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

}

void App::specialKeyUp(int key) {

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

