#include "components.h"
#include "texture.h"

#include <ctime>
#include <cstdlib>

using namespace std;


GLuint chip_textures[2];

void draw_face(GLfloat p1[3], GLfloat p2[3], GLfloat p3[3], GLfloat p4[3]) {
	glNormal3fv(p1);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(p1);

	glNormal3fv(p2);
	glTexCoord2f(0.0, 1.0); 
	glVertex3fv(p2);

	glNormal3fv(p3);
	glTexCoord2f(1.0, 1.0); 
	glVertex3fv(p3);

	glNormal3fv(p4);
	glTexCoord2f(1.0, 0.0); 	
	glVertex3fv(p4);

}

void polygon_face(GLfloat color[3], GLfloat p1[3], GLfloat p2[3], GLfloat p3[3], GLfloat p4[3]) {
	glBegin(GL_POLYGON);
	glColor3fv(color);
	
	glNormal3fv(p1);
	glVertex3fv(p1);
	
	glNormal3fv(p2);
	glVertex3fv(p2);
	
	glNormal3fv(p3);
	glVertex3fv(p3);
	
	glNormal3fv(p4);
	glVertex3fv(p4);

	glEnd();
}

void chip(GLfloat height) {
	GLfloat width = 0.03;
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

	glBegin(GL_QUADS);
	draw_face(points[0], points[1], points[2], points[3]);
	draw_face(points[4], points[5], points[6], points[7]);
	draw_face(points[0], points[1], points[5], points[4]);
	draw_face(points[1], points[2], points[6], points[5]);
	draw_face(points[2], points[3], points[7], points[6]);
	draw_face(points[3], points[0], points[4], points[7]);
	glEnd();
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

	// Drawing bottom of chip box
	polygon_face(white, points[0], points[1], points[2], points[3]);

	char filename[] = "texture/mcdonald.jpg";
	init_texture(chip_textures, 2);
	set_texture(chip_textures, 0, filename);

	// Drawing sides of chip box
	glBegin(GL_QUADS);
	draw_face(points[0], points[4], points[5], points[1]);
	draw_face(points[1], points[5], points[6], points[2]);
	draw_face(points[2], points[6], points[7], points[3]);
	draw_face(points[3], points[7], points[4], points[0]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void chips() {
	GLfloat translateX, translateY, translateZ, length, transX_range, transZ_range;

	chip_box();
	srand((unsigned)time(NULL));

	char filename[] = "texture/chip.jpg";
	set_texture(chip_textures, 1, filename);

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

	glDisable(GL_TEXTURE_2D);
}
