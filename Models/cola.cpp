//#include "stdafx.h"
#include<stdio.h>
#include <math.h>
//#define GL_GLEXT_PROTOTYPES

#include <glut.h>


// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;
#define M_PI 3.14159265357

GLfloat vertices[][3] = { { -0.5, -0.5, -0.5 }, { 0.5, -0.5, -0.5 },
{ 0.5, 0.5, -0.5 }, { -0.5, 0.5, -0.5 }, { -0.5, -0.5, 0.5 },
{ 0.5, -0.5, 0.5 }, { 0.5, 0.5, 0.5 }, { -0.5, 0.5, 0.5 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 },
{ 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

GLubyte cubeIndices[24] = { 0, 3, 2, 1, 2, 3, 7, 6,
0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------

void cola(){
	float v[2601][3];//points, (sectors+1)*(ring+1)
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
			if (i >= 30 && i <= 32){
				y = h / rings *(i-1);
				x = coverRadius * cos(2*j*M_PI / sectors);
				z = coverRadius * sin(2*j*M_PI / sectors);
				v[i*(sectors + 1) + j][0] = x;
				v[i*(sectors + 1) + j][1] = y;
				v[i*(sectors + 1) + j][2] = z;
				continue;
			}
			//Control the straw zone
			if (i > 33 && i < rings){
				y = h / rings *(i-1);
				x = strawRadius * cos(2*j*M_PI / sectors);
				z = strawRadius * sin(2*j*M_PI / sectors);
				v[i*(sectors + 1) + j][0] = x;
				v[i*(sectors + 1) + j][1] = y;
				v[i*(sectors + 1) + j][2] = z;
				continue;
			}
			if (i == 0)//the end layer
			{
				v[i*(sectors + 1) + j][0] = 0;
				v[i*(sectors + 1) + j][1] = 0;
				v[i*(sectors + 1) + j][2] = 0;
			}else if (i == rings) // top layer
			{
				v[i*(sectors + 1) + j][0] = 0;
				v[i*(sectors + 1) + j][1] = h / rings * (rings - 2);
				v[i*(sectors + 1) + j][2] = 0;
			}else{
				y = h / rings *(i-1);
				x = Radius * cos(2*j*M_PI / sectors);
				z = Radius * sin(2*j*M_PI / sectors);
				v[i*(sectors + 1) + j][0] = x;
				v[i*(sectors + 1) + j][1] = y;
				v[i*(sectors + 1) + j][2] = z;
			}
		}
		// Control the Radius to increase
		Radius = Radius +0.0012;
	}

	// record the information of the rectangle
	int np = 0; // number of rectangles
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

void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();


	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	cola();



	glFlush();
	glutSwapBuffers();

}
// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){

	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutCreateWindow("Cola");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}
