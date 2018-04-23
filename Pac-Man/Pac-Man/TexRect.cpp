#include "TexRect.h"


TexRect::TexRect (const char* animation, const char* default_img, int rows, int cols, float x=0, float y=0, float w=0.5, float h=0.5)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	//for animated frames//
	RgbImage aniTexMap( animation );

	glGenTextures( 1, &anim_tex_id );
	glBindTexture( GL_TEXTURE_2D, anim_tex_id );
    
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, aniTexMap.GetNumCols(), aniTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, aniTexMap.ImageData() );

	this->anim_tex_id = anim_tex_id;
    
	//for default static image//
	RgbImage defTexMap( default_img );

	glGenTextures( 1, &default_tex_id );
	glBindTexture( GL_TEXTURE_2D, default_tex_id );
    
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, defTexMap.GetNumCols(), defTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, defTexMap.ImageData() );

	this->default_tex_id = default_tex_id;


	//for all//
	this->rows = rows;
	this->cols = cols;
    
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
    
	curr_row = 1;
	curr_col = 1;
    
	complete = false;
	ani_toggle = false;
}

bool TexRect::done() {
    return complete;
}

void TexRect::draw()
{
    if (ani_toggle == false)
    {
        glBindTexture(GL_TEXTURE_2D, default_tex_id);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glBegin(GL_QUADS);

        glTexCoord2f(0, 0);
        glVertex2f(x, y - h);
    
        glTexCoord2f(0, 1);
        glVertex2f(x, y);
    
        glTexCoord2f(1, 1);
        glVertex2f(x+w, y);
    
        glTexCoord2f(1, 0);
        glVertex2f(x+w, y - h);

        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
	if (ani_toggle == true)
    {
        glBindTexture(GL_TEXTURE_2D, anim_tex_id);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        float xinc = 1.0 / cols;
        float yinc = 1.0 / rows;

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
void TexRect::incY(){
    y+=0.01;
}

void TexRect::advance()
{
    if (curr_col < cols){
        curr_col++;
    }
    else 
	{
        if (curr_row < rows){
            curr_row++;
            curr_col = 1;
        }
        else{
            curr_row = 1;
            curr_col = 1;
        }
    }
    
    if (curr_row == rows && curr_col == cols){
        complete = true;
    }
}

void TexRect::toggle()
{
	this->ani_toggle = true;
}

void TexRect::toggleReset()
{
	this->ani_toggle = false;
}

void TexRect::reset()
{	complete = false;
}

bool TexRect::contains(float testX, float testY)
{	
	if(testX >= x && testX <= (x + w) && testY <= y && testY >= (y - h))
	{	return true;	}
	else
	{	return false;	}

}








