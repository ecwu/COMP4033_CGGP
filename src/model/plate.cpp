#include "components.h"

using namespace std;


void draw_plane(float x, float z)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-x, 0, -z);
	glVertex3f(x, 0, -z);
	glVertex3f(x, 0, z);
	glVertex3f(-x, 0, z);
	glEnd();
}

void draw_board(float x, float y) {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-x, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, y, 0);
	glVertex3f(-x, y, 0);
	glEnd();
}

void draw_curve_board(float x, float low_y, float high_y) {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-x, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, low_y, 0);
	glVertex3f(x / 2, high_y, 0);
	glVertex3f(-x / 2, high_y, 0);
	glVertex3f(-x, low_y, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-x / 2, high_y, 0);
	glVertex3f(x / 2, high_y, 0);
	glVertex3f(x / 2, high_y, 0.05);
	glVertex3f(-x / 2, high_y, 0.05);
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
