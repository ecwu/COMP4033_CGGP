#include "components.h"

using namespace std;

void cola() {
	float v[2601][3];// Points, (sectors+1)*(ring+1)
	float Radius = 0.1;// Body
	float strawRadius = 0.008;// straw
	float coverRadius = 0.16; // Cover
	float h = 0.8;

	int sectors = 50;
	int rings = 50;

	// Initialize the coordinate system
	float x, y, z;

	// Set the value for each points
	for (int i = 0; i < rings + 1; i++)
	{
		for (int j = 0; j < sectors + 1; j++)
		{
			// Control the cover zone
			if (i >= 30 && i <= 32) {
				y = h / rings * (i - 1);
				x = coverRadius * cos(2 * j * M_PI / sectors);
				z = coverRadius * sin(2 * j * M_PI / sectors);
				v[i * (sectors + 1) + j][0] = x;
				v[i * (sectors + 1) + j][1] = y;
				v[i * (sectors + 1) + j][2] = z;
				continue;
			}
			// Control the straw zone
			if (i > 33 && i < rings) {
				y = h / rings * (i - 1);
				x = strawRadius * cos(2 * j * M_PI / sectors);
				z = strawRadius * sin(2 * j * M_PI / sectors);
				v[i * (sectors + 1) + j][0] = x;
				v[i * (sectors + 1) + j][1] = y;
				v[i * (sectors + 1) + j][2] = z;
				continue;
			}
			if (i == 0)// The end layer
			{
				v[i * (sectors + 1) + j][0] = 0;
				v[i * (sectors + 1) + j][1] = 0;
				v[i * (sectors + 1) + j][2] = 0;
			}
			else if (i == rings) // Top layer
			{
				v[i * (sectors + 1) + j][0] = 0;
				v[i * (sectors + 1) + j][1] = h / rings * (rings - 2);
				v[i * (sectors + 1) + j][2] = 0;
			}
			else {
				y = h / rings * (i - 1);
				x = Radius * cos(2 * j * M_PI / sectors);
				z = Radius * sin(2 * j * M_PI / sectors);
				v[i * (sectors + 1) + j][0] = x;
				v[i * (sectors + 1) + j][1] = y;
				v[i * (sectors + 1) + j][2] = z;
			}
		}
		// Control the Radius to increase
		Radius = Radius + 0.0012;
	}

	// Record the information of the rectangle
	int np = 0; // Number of rectangles
	int pIndex[10404]; // Record each points coordinate
	for (int i = 0; i < rings; i++)
	{
		for (int j = 0; j < sectors; j++)
		{
			pIndex[4 * np + 0] = i * (sectors + 1) + j;
			pIndex[4 * np + 1] = i * (sectors + 1) + (j + 1);
			pIndex[4 * np + 2] = (i + 1) * (sectors + 1) + (j + 1);
			pIndex[4 * np + 3] = (i + 1) * (sectors + 1) + j;
			np++;
		}
	}


	for (int i = 0; i < np; i++) { // i: index for polygon
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3fv(v[pIndex[4 * i + 0]]);
		glVertex3fv(v[pIndex[4 * i + 1]]);
		glVertex3fv(v[pIndex[4 * i + 2]]);
		glVertex3fv(v[pIndex[4 * i + 3]]);
		glEnd();
	}
}
