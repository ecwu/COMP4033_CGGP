#include "components.h"

using namespace std;


GLfloat rotate_y = 0;
GLfloat rotate_x = 0;

void draw() {
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	plate();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, -0.5, 0.4);
	glScalef(0.8, 0.8, 0.8);
	cola();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, -0.25, -0.2);
	glScalef(0.6, 0.6, 0.6);
	burger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.38, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	chips();
	glPopMatrix();
}

void display() {
	// Clear screen and buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	// Main function of drawings
	draw();

	glFlush();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}


// specialKeys() Callback Function
void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	// Request display update
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {
	// Initialize GLUT
	glutInit(&argc, argv);

	// Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutInitWindowSize(500, 500);
	glutCreateWindow("McDonald");

	// Enable Z-buffer
	glEnable(GL_DEPTH_TEST);

	// Callback Functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	// Pass control to GLUT for events
	glutMainLoop();

	return 0;
}
