#include "components.h"
#include "texture.h"

using namespace std;


GLuint cola_textures[2];

void cola(){
	glPushMatrix();
	init_texture(cola_textures, 2);
	set_texture(cola_textures, 0, "texture/cola_texture.bmp");

	// Draw bottle body
    glBegin( GL_QUAD_STRIP);
	int nslice = 20;
	double topR = 0.2;
	double bottomR = 0.15;
	double height = 0.7;
    double t = 0.0;double dt = 2*M_PI/nslice;
    for (int j = 0; j <= nslice; ++j) 
	{
       glTexCoord2f( t/(2*M_PI), 1.0); 
	   glVertex3f( bottomR*cos( t), 0.0, -1*bottomR*sin(t));

       glTexCoord2f( t/(2*M_PI), 0.0); 
	   glVertex3f( topR*cos( t), height, -1*topR*sin(t));

	   t = t + dt;
     }
    glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Straw
	glPushMatrix();
	set_texture(cola_textures, 1, "texture/straw_texture.bmp");

    glBegin( GL_QUAD_STRIP);
	nslice = 20;
	topR = 0.02;
	bottomR = 0.015;
	height = 1;
    t = 0.0; dt = 2*M_PI/nslice;
    for (int j = 0; j <= nslice; ++j) 
	{
       glTexCoord2f( t/(2*M_PI), 1.0); 
	   glVertex3f( topR*cos( t), height, -1*topR*sin(t));
       glTexCoord2f( t/(2*M_PI), 0.0); 
	   glVertex3f( bottomR*cos( t), 0.0, -1*bottomR*sin(t));
       
	   t = t + dt;
     }
    glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
