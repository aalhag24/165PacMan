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

	/**
	explode(0);
    glutTimerFunc(20, move, 1);
	**/
}

void App::draw() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set Color
	glColor3d(1.0, 1.0, 1.0);

	MainFrame.draw();

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

	MainFrame.Handle(x, y);
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
	MainFrame.keyPressHandle(key); 
}

