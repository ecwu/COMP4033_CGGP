#include "components.h"
#include "texture.h"
#include <ctime>
#include <cstdlib>
using namespace std;

GLuint burger_textures[4];

void sphere()
{
	float v[961][3];//points, sector+1
	float Radius = 0.5;
	int sectors = 30;
	int rings = 30;
	float x, y, z;
	//angle = 36, curve = PI / 5;
	//Points value
	for (int i = 0; i < rings + 1; i++)
	{
		for (int j = 0; j < sectors + 1; j++)
		{
			//float const z = cos(2 * M_PI * r * R);
			//float const x = sin(2 * M_PI * r * R) * cos(2 * M_PI * s * S);
			//float const y = sin(2 * M_PI * r * R) * sin(2 * M_PI * s * S);

			y = Radius * cos(i * M_PI / rings) / 2.5;
			x = Radius * sin(i * M_PI / rings) * cos(2 * j * M_PI / sectors);
			z = Radius * sin(i * M_PI / rings) * sin(2 * j * M_PI / sectors);
			v[i * (sectors + 1) + j][0] = x;
			v[i * (sectors + 1) + j][1] = y;
			v[i * (sectors + 1) + j][2] = z;
		}
	}
	int np = 0;
	int index[4000];
	for (int i = 0; i < rings / 2; i++) { // r: index for ring
		for (int j = 0; j < sectors; j++) { // s: index for sector
			index[4 * np + 0] = i * (sectors + 1) + j;
			index[4 * np + 1] = i * (sectors + 1) + (j + 1);
			index[4 * np + 2] = (i + 1) * (sectors + 1) + (j + 1);
			index[4 * np + 3] = (i + 1) * (sectors + 1) + j;
			np++;
		}
	}

	for (int i = 0; i < np; i++) { // i: index for polygon
		glBegin(GL_QUADS);
		glVertex3fv(v[index[4 * i + 0]]);
		glVertex3fv(v[index[4 * i + 1]]);
		glVertex3fv(v[index[4 * i + 2]]);
		glVertex3fv(v[index[4 * i + 3]]);
		glEnd();
	}

}


void burger() {
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	init_texture(burger_textures, 4);

	// Uncomment the object name
	glPushMatrix();
		glPushMatrix();
			glTranslated(0, 0.15, 0);
			glColor3f(1.0, 0.686, 0.067);
			sphere();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.15, 0);
	glRotatef(180, 1.0, 0.0, 0.0);
	sphere();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	char filename[] = "bun.jpg";
	set_texture(burger_textures, 0, filename);
	glPushMatrix();
	glTranslated(0, 0.1 / 2, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.337, 0.18, 0.078);
	gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslated(0, 0.1 / 2, 0);
	glTranslated(0, -0.1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.321, 0.247);
	gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.1 / 2, 0);
	glTranslated(0, 0.1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.247, 1.0, 0.337);
	gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
	glPopMatrix();
}
