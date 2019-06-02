#include <stdio.h>
#include <math.h>
//#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
static GLfloat mat_specular[] = { 1.0,1.0,1.0,1.0 };
static GLfloat mat_shininess[] = { 50.0 };
static GLfloat light_position0[] = { 1.0,1.0,1.0,0.0 };
static GLfloat light[] = { 1.0,1.0,1.0,1.0 };
static GLfloat lmodel_ambient[] = { 0.1,0.1,0.1,1.0 };
static GLint flat_smooth = GL_SMOOTH;


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
    glVertex3f(x/2, high_y, 0);
    glVertex3f(-x/2, high_y, 0);
    glVertex3f(-x, low_y, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-x/2, high_y, 0);
    glVertex3f(x/2, high_y, 0);
    glVertex3f(x/2, high_y, 0.05);
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

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void display(){

    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    glShadeModel(flat_smooth);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // point light
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    plate();
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
    glutCreateWindow("project");
    init();
    // Callback functions
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    //  Pass control to GLUT for events
    glutMainLoop();

    //  Return to OS
    return 0;

}
