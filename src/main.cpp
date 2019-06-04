#include "components.h"

using namespace std;

// GLfloat rotate_y = 0;
// GLfloat rotate_x = 0;

GLfloat position0[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat position1[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_emission[] = { 0.05, 0.05, 0.05, 0.0 };
GLfloat light_ambient_white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient_blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat light_ambient_red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat blue_light[] = {0.0, 0.0, 1.0, 1.0};
GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
GLfloat red_light[] = {1.0, 0.0, 0.0, 1.0};
GLfloat spot_position[] = {0.0, 0.0, 0.0, 1.0};

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	// Enable Z-buffer
	glEnable(GL_DEPTH_TEST);
}

void draw() {
	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	plate();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, -0.3, 0.4);
	glScalef(0.8, 0.8, 0.8);
	cola();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, -0.05, -0.3);
	glScalef(0.6, 0.6, 0.6);
	burger();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.18, -0.1);
	glRotatef(120, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	chips();
	glPopMatrix();
}

void display() {


	// Clear screen and buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	// Reset transformations
	glLoadIdentity();
	gluPerspective(28.0, 1, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.5, 2, -2.5, 0, -0.3, 0, 0, 1, 0);

	glPushMatrix();
    // Set the light 0 position
    position0[0] = 5;
    position0[1] = 5;
    position0[2] = 5;
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_EMISSION, white_light);
    // glTranslated(0.0, 0.0, 5.0);
    glPopMatrix();

	glPushMatrix();
	position1[0] = 2;
    position1[1] = 10;
    position1[2] = 10;

    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient_white);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT1, GL_EMISSION, white_light);
    // spotlight
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_position);
    glPopMatrix();

	// glPushMatrix();
    // Set Material
	// 	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	// 	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	// 	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	// 	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	// 	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    // glPopMatrix();

	draw();

	// glRotatef(rotate_x, 1.0, 0.0, 0.0);
	// glRotatef(rotate_y, 0.0, 1.0, 0.0);

	// Main function of drawings
	// draw();

	glFlush();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}


// specialKeys() Callback Function
// void specialKeys(int key, int x, int y) {
// 	if (key == GLUT_KEY_RIGHT)
// 		rotate_y += 5;

// 	else if (key == GLUT_KEY_LEFT)
// 		rotate_y -= 5;

// 	else if (key == GLUT_KEY_UP)
// 		rotate_x += 5;

// 	else if (key == GLUT_KEY_DOWN)
// 		rotate_x -= 5;

// 	// Request display update
// 	glutPostRedisplay();
// }


int main(int argc, char* argv[]) {
	// Initialize GLUT
	glutInit(&argc, argv);

	// Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create window
	glutInitWindowSize(500, 500);
	glutCreateWindow("McDonald");
	init();

	// Callback Functions
	glutDisplayFunc(display);
	// glutSpecialFunc(specialKeys);

	// Pass control to GLUT for events
	glutMainLoop();

	return 0;
}
