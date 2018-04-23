// Pac-Man.cpp : Defines the entry point for the console application.
//

#include "App.h"
#include "stdafx.h"

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Instantiate a new App
	App* myApp = new App("Pac-Man", 50, 50, 720, 800);

	// Start the app
	myApp->run();
}
