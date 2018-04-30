#ifndef AnimatedRect_h
#define AnimatedRect_h

#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include <SOIL.h>
#else
#include <GL/freeglut.h>
#include <SOIL.h>
#endif

class AnimatedRect {
    float x;
    float y;
    float w;
    float h;
    GLuint texture_map_id;
    
    int rows;
    int cols;
    
    int curr_row;
    int curr_col;

    bool complete;
    bool animating;
public:
    AnimatedRect (const char*, int, int, float, float, float, float);
    
	void (AnimatedRect::*DIR)();
	//DIR = &Idle;
	bool contains(float, float);
    
    void draw();
    void advance();
    
    void incY(float);
	void decY(float);
	void incX(float);
	void decX(float);
	void Idle();
    
    void animate();
	void reset();
    void stop();

	bool done();

	void setPos(const char);
	float getw()const;
	float geth()const;
};

#endif
