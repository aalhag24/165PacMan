#ifndef TexRect_h
#define TexRect_h

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "RgbImage.h"

class TexRect 
{	
	float x;
	float y;
	float w;
	float h;
	GLuint default_tex_id;
	GLuint anim_tex_id;
	int rows;
	int cols;
    
	int curr_row;
	int curr_col;
    
	bool complete;

 public:

	bool ani_toggle;

	TexRect (const char*, const char*, int, int, float, float, float, float);
    
	bool done();
    
	void draw();
    
	void advance();
    
	void incY();
    
	void reset();

	void toggle();

	void toggleReset();

	bool contains(float testX, float testY);
};

#endif
