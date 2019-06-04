#include "components.h"
#include "texture.h"

using namespace std;


GLuint plate_texture[1];

void draw_plane(float x, float z)
{
    init_texture(plate_texture, 1);
	set_texture(plate_texture, 0, "texture/cola_texture.bmp");
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glNormal3f(-x, 0, z);
    glVertex3f(-x, 0, z);

    glTexCoord2f(0.0, 1.0);
    glNormal3f(-x, 0, -z);
    glVertex3f(-x, 0, -z);

    glTexCoord2f(1.0, 1.0);
    glNormal3f(x, 0, -z);
    glVertex3f(x, 0, -z);

    glTexCoord2f(1.0, 0.0);
    glNormal3f(x, 0, z);
    glVertex3f(x, 0, z);

    glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw_board(float x, float y) {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(-x, 0, 0);
    glVertex3f(-x, 0, 0);
    glNormal3f(x, 0, 0);
    glVertex3f(x, 0, 0);
    glNormal3f(x, y, 0);
    glVertex3f(x, y, 0);
    glNormal3f(-x, y, 0);
    glVertex3f(-x, y, 0);
    glEnd();
}

void draw_curve_board(float x, float low_y, float high_y) {
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(-x, 0, 0);
    glVertex3f(-x, 0, 0);
    glNormal3f(x, 0, 0);
    glVertex3f(x, 0, 0);
    glNormal3f(x, low_y, 0);
    glVertex3f(x, low_y, 0);
    glNormal3f(x/2, high_y, 0);
    glVertex3f(x/2, high_y, 0);
    glNormal3f(-x/2, high_y, 0);
    glVertex3f(-x/2, high_y, 0);
    glNormal3f(-x, low_y, 0);
    glVertex3f(-x, low_y, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-x/2, high_y, 0);
    glVertex3f(-x/2, high_y, 0);
    glNormal3f(x/2, high_y, 0);
    glVertex3f(x/2, high_y, 0);
    glNormal3f(x/2, high_y, 0.05);
    glVertex3f(x/2, high_y, 0.05);
    glNormal3f(-x/2, high_y, 0.05);
    glVertex3f(-x/2, high_y, 0.05);
    glEnd();
}

void plate() {
    glPushMatrix();
    draw_plane(0.8, 0.6);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.6);
    draw_board(0.8, 0.08);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.6);
    draw_board(0.8, 0.08);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.8);
    draw_curve_board(0.6, 0.08, 0.12);
    glPopMatrix();

    glTranslatef(0.0, 0.0, -0.8);
    glRotatef(180, 0.0, 1.0, 0.0);
    draw_curve_board(0.6, 0.08, 0.12);
    glPopMatrix();

    glPopMatrix();
}
