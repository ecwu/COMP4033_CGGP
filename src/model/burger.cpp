#include "components.h"
#include "texture.h"
#include <ctime>
#include <cstdlib>
using namespace std;

GLuint burger_textures[5];

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

	int t = 0;
	int index2[4 * rings/2 * sectors];
	float ti[4 * rings/2 * sectors][2];
	for (int r = 0; r < rings / 2 - 1; r++) {
		for (int s = 0; s < sectors; s++) {
			index2[4 * t + 0] = r * sectors + s;
			index2[4 * t + 1] = r * sectors + (s + 1);
			index2[4 * t + 2] = (r + 1) * sectors + (s + 1);
			index2[4 * t + 3] = (r + 1) * sectors + s;

			ti[4 * t + 0][0] = r;
			ti[4 * t + 0][1] = s;

			ti[4 * t + 1][0] = r;
			ti[4 * t + 1][1] = s + 1;

			ti[4 * t + 2][0] = r + 1;
			ti[4 * t + 2][1] = s + 1;

			ti[4 * t + 3][0] = r + 1;
			ti[4 * t + 3][1] = s;

			t++;
		}
	}

	for (int i = 0; i < np; i++) { // i: index for polygon
		glBegin(GL_QUADS);
		
		glNormal3fv(v[index[4 * i + 0]]);
		// glTexCoord2f(0.0, 0.0);
		glTexCoord2d(ti[4 * i + 0][1] / sectors, ti[4 * i + 0][0] / rings / 2);
		glVertex3fv(v[index[4 * i + 0]]);

		glNormal3fv(v[index[4 * i + 1]]);
		// glTexCoord2f(0.0, 1.0);
		glTexCoord2d(ti[4 * i + 1][1] / sectors, ti[4 * i + 1][0] / rings / 2);
		glVertex3fv(v[index[4 * i + 1]]);

		glNormal3fv(v[index[4 * i + 2]]);
		// glTexCoord2f(1.0, 1.0);
		glTexCoord2d(ti[4 * i + 2][1] / sectors, ti[4 * i + 2][0] / rings / 2);
		glVertex3fv(v[index[4 * i + 2]]);

		glNormal3fv(v[index[4 * i + 3]]);
		// glTexCoord2f(1.0, 0.0);
		glTexCoord2d(ti[4 * i + 3][1] / sectors, ti[4 * i + 3][0] / rings / 2);
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
	init_texture(burger_textures, 5);

	char bun[] = "texture/bun-t.jpg";
	set_texture(burger_textures, 3, bun);
	glPushMatrix();
		glTranslated(0, 0.15, 0);
		glColor3f(1.0, 0.686, 0.067);
		sphere();
	glPopMatrix();

	char bunb[] = "texture/bun-b.jpg";
	set_texture(burger_textures, 4, bunb);
	glPushMatrix();
	glTranslated(0, -0.15, 0);
	glRotatef(180, 1.0, 0.0, 0.0);
	sphere();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	char filename[] = "texture/bun.jpg";
	set_texture(burger_textures, 0, filename);
	glPushMatrix();
	glTranslated(0, 0.1 / 2, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.337, 0.18, 0.078);
	gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
	glPopMatrix();

	char filename1[] = "texture/tomato.jpg";
	set_texture(burger_textures, 1, filename1);
	glPushMatrix();
	glTranslated(0, 0.1 / 2, 0);
	glTranslated(0, -0.1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.321, 0.247);
	gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
	glPopMatrix();

	char filename2[] = "texture/green.jpg";
	set_texture(burger_textures, 2, filename2);
	glPushMatrix();
	glTranslated(0, 0.1 / 2, 0);
	glTranslated(0, 0.1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.247, 1.0, 0.337);
	gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
	glPopMatrix();
}
