#ifndef App_hpp
#define App_hpp

#include "stdafx.h"

#include "GlutApp.h"
#include "TexRect.h"
#include "AnimatedRect.h"

#include "Board.h"

class App : public GlutApp {
	// Maintain app state here
	float mx;
	float my;
public:
	// Constructor, to initialize state
	App(const char* label, int x, int y, int w, int h);

	// These are the events we want to handle
	void draw();
	void keyPress(unsigned char key);
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);

	void specialKeyPress(int key);

	void specialKeyUp(int key);

	void idle();


	Board *MainFrame;
	//TexRect* background;
};


#endif
