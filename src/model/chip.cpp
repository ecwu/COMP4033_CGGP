#include "components.h"

#include <ctime>
#include <cstdlib>

using namespace std;


void polygon_face(GLfloat color[3], GLfloat p1[3], GLfloat p2[3], GLfloat p3[3], GLfloat p4[3]) {
	glBegin(GL_POLYGON);
	glColor3fv(color);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glEnd();
}

void chip(GLfloat height) {
	GLfloat width = 0.03;
	GLfloat yellow[] = { 1.0, 1.0, 0.0 };
	GLfloat points[8][3];
	
	// Initialize points
	for (int i = 0; i < 8; i++) {
		if (i < 4) {
			points[i][0] = -height;
			points[i][1] = i < 2 ? width : -width;
			points[i][2] = i % 3 == 0 ? width : -width;
		}
		else {
			points[i][0] = height;
			points[i][1] = i < 6 ? width : -width;
			points[i][2] = (i - 4) % 3 == 0 ? width : -width;
		}
	}


	// Drawing top and bottom of chip
	polygon_face(yellow, points[0], points[1], points[2], points[3]);
	polygon_face(yellow, points[4], points[5], points[6], points[7]);

	// Drawing sides of chip
	polygon_face(yellow, points[0], points[1], points[5], points[4]);
	polygon_face(yellow, points[1], points[2], points[6], points[5]);
	polygon_face(yellow, points[2], points[3], points[7], points[6]);
	polygon_face(yellow, points[3], points[0], points[4], points[7]);
}

void chip_box() {
	GLfloat width = 0.3, length = 0.6, height = 0.2;
	GLfloat white[] = { 1.0, 1.0, 1.0 };
	GLfloat points[8][3];

	// Initialize points
	for (int i = 0; i < 8; i++) {
		if (i < 4) {
			points[i][0] = i < 2 ? length : -length;
			points[i][1] = -height;
			points[i][2] = i % 3 == 0 ? width : -width;
		}
		else {
			points[i][0] = i < 6 ? length * 1.3 : -length * 1.3;
			points[i][1] = height;
			points[i][2] = (i - 4) % 3 == 0 ? width * 1.3 : -width * 1.3;
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);

	// Drawing bottom of chip box
	polygon_face(white, points[0], points[1], points[2], points[3]);

	// Drawing sides of chip box
	polygon_face(white, points[0], points[1], points[5], points[4]);
	polygon_face(white, points[1], points[2], points[6], points[5]);
	polygon_face(white, points[2], points[3], points[7], points[6]);
	polygon_face(white, points[3], points[0], points[4], points[7]);
}

void chips() {
	GLfloat translateX, translateY, translateZ, length, transX_range, transZ_range;

	chip_box();
	srand((unsigned)time(NULL));

	for (int i = 0; i < 100; i++) {
		length = rand() % 4 * 1.0 / 10 + 0.1;
		translateY = 0.25 - rand() % 4 * 1.0 / 10;
		transX_range = 0.6 * 1.3 * (translateY + 0.2) / 0.4 - length;
		transZ_range = 0.3 * 1.3 * (translateY + 0.2) / 0.4 - 0.03;
		if (transX_range < 0.01)
			translateX = 0;
		else
			translateX = transX_range - rand() % (int)(transX_range * 100) * 2.0 / 100;
		if (transZ_range < 0.01)
			translateZ = 0;
		else
			translateZ = transZ_range - rand() % (int)(transZ_range * 100) * 2.0 / 100;


		glPushMatrix();
		glTranslatef(translateX, translateY, translateZ);
		chip(length);
		glPopMatrix();
	}
}
