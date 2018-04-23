#include "App.h"
#include "App.h"
#include "stdafx.h"
#include <freeglut.h>

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

**/
App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	// Initialize state variables
	singleton = this;

	mx = 0.0;
	my = 0.0;

	char* wall_file, painting_file;

	//background = new TexRect("wall.bmp", -1, 1, 2, 2);
	painting = new TexRect("explode.bmp", "mushroom.bmp", 5, 5, 0, 0.67, 0.5, 0.5);

	isMoving = false;

	/**
	explode(0);
    glutTimerFunc(20, move, 1);
	**/
}

void App::draw() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Color
	glColor3d(1.0, 1.0, 1.0);

	// Draw some points
	glBegin(GL_POINTS);

	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);

	glEnd();




	// Draw a yellow cross
	glColor3d(1.0, 1.0, 0.0);

	glBegin(GL_LINES);

	glVertex2f(mx - 0.05f, my);
	glVertex2f(mx + 0.05f, my);

	glVertex2f(mx, my - 0.05f);
	glVertex2f(mx, my + 0.05f);

	glEnd();
	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Color
	glColor3d(1.0, 1.0, 1.0);

	painting->draw();

	//background->draw();

	glDisable(GL_TEXTURE_2D);

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

void App::mouseDown(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	/**
	if(painting->contains(mx, my) && !painting->ani_toggle){
		painting->toggle();
		painting->reset();
		explode(0);
	}

	**/
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

void App::keyUp(unsigned char key) {}

void App::keyPress(unsigned char key) {
	if (key == 27) {			// Exit the app when Esc key is pressed
		delete painting;    //delete background;
		exit(0);
	}
	else if (key == ' ') {
		painting->reset();
		painting->toggleReset();
		redraw();
	}

	else if (key == '1') {
		painting->toggleReset();
	}

}

