#include "stdafx.h"
#include "AnimatedRect.h"

AnimatedRect::AnimatedRect (const char* map_filename, int rows, int cols, float x=0, float y=0, float w=0.5, float h=0.5)
{   
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    
    texture_map_id = SOIL_load_OGL_texture
    (
     map_filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    this->rows = rows;
    this->cols = cols;
    
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    curr_row = 1;
    curr_col = 1;
    
    complete = false;
    animating = false;
	paniced = false;
	Adv = true;
}

void AnimatedRect::draw(){
	if (rows == 1 && cols == 1) {
		glBindTexture(GL_TEXTURE_2D, texture_map_id);
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);
		glColor4f(1, 1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex2f(x, y - h);

		glTexCoord2f(0, 1);
		glVertex2f(x, y);

		glTexCoord2f(1, 1);
		glVertex2f(x + w, y);

		glTexCoord2f(1, 0);
		glVertex2f(x + w, y - h);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	else {
		if (animating) {
			glBindTexture(GL_TEXTURE_2D, texture_map_id);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);



			float xinc = 1.0f / (float)cols;
			float yinc = 1.0f / (float)rows;


			float top = 1 - yinc * (curr_row - 1);
			float bottom = 1 - yinc * curr_row;

			float left = xinc * (curr_col - 1);
			float right = xinc * curr_col;

			glBegin(GL_QUADS);

			glTexCoord2f(left, bottom);
			glVertex2f(x, y - h);

			glTexCoord2f(left, top);
			glVertex2f(x, y);

			glTexCoord2f(right, top);
			glVertex2f(x + w, y);

			glTexCoord2f(right, bottom);
			glVertex2f(x + w, y - h);

			glEnd();

			glDisable(GL_TEXTURE_2D);
		}
	}
}

void AnimatedRect::incY(float Y = 0.01f) { y += Y; }
void AnimatedRect::decY(float Y = 0.01f) { y -= Y; }
void AnimatedRect::incX(float X = 0.01f) { x += X; }
void AnimatedRect::decX(float X = 0.01f) { x -= X; }
void AnimatedRect::Idle(float noValue) {}

void AnimatedRect::reset() { complete = false; }
void AnimatedRect::animate() { animating = true; }
void AnimatedRect::stop() { animating = false; }
void AnimatedRect::pause() { Adv = false; }
void AnimatedRect::resume() { Adv = true; }

bool AnimatedRect::contains(float mx, float my) {
	return mx >= x && mx <= x + w && my <= y && my >= y - h;
}
bool AnimatedRect::done() { return complete; }

void AnimatedRect::Shift(char D) {
	switch (D) {
		case 'R': incX(); break;
		case 'L': decX(); break;
		case 'D': decY(); break;
		case 'U': incY(); break;
		default:  break;
	}
}
void AnimatedRect::setPos(const char D){
	switch (D){
		case 'R': curr_row = 1; break;
		case 'L': curr_row = 2; break;
		case 'D': curr_row = 3; break;
		case 'U': curr_row = 4; break;
		default:   break;
	}
}

void AnimatedRect::setx(const float X){
	x = X;
}

void AnimatedRect::sety(const float Y){
	y = Y;
}

float AnimatedRect::getx() const{ return x; }
float AnimatedRect::gety() const { return y; }
float AnimatedRect::getw() const { return w; }
float AnimatedRect::geth() const { return h; }

void AnimatedRect::advance() {
	if (Adv) {
		if (curr_col < cols) {
			curr_col++;
		}
		else {
			curr_col = 1;
		}
	}
}

void AnimatedRect::setRow(int a) {
	curr_col = a;
}