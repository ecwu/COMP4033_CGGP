// File:        task1.cpp
// Author:      Matt Daisley & Zhenghao Wu
// Created:     4/25/2012
// Edited:      3/07/2019
// Project:     Source code for Make sphere, cylinder, double cone and capsule
// Description: Creates an OpenGL window and draws a 3D object
//              That the user can rotate using the arrow keys
//
// Controls:    Left Arrow  - Rotate Left
//              Right Arrow - Rotate Right
//              Up Arrow    - Rotate Up
//              Down Arrow  - Rotate Down

#include <math.h>
//#define GL_GLEXT_PROTOTYPES

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <stdio.h>


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


void sphere()
{
    float v[961][3];//points, sector+1
    float Radius = 0.5;
    int sectors = 30;
    int rings = 30;
    float x, y, z;
    //angle = 36, curve = PI / 5;
    //Points value
    for (int i = 0; i < rings+1; i++)
    {
        for (int j = 0; j < sectors+1; j++)
        {
            //float const z = cos(2 * M_PI * r * R);
            //float const x = sin(2 * M_PI * r * R) * cos(2 * M_PI * s * S);
            //float const y = sin(2 * M_PI * r * R) * sin(2 * M_PI * s * S);
            
            y = Radius * cos(i*M_PI / rings) / 2.5;
            x = Radius * sin(i*M_PI / rings)*cos(2*j*M_PI / sectors);
            z = Radius * sin(i*M_PI / rings)*sin(2*j*M_PI / sectors);
            v[i*(sectors + 1) + j][0] = x;
            v[i*(sectors + 1) + j][1] = y;
            v[i*(sectors + 1) + j][2] = z;
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
        glBegin(GL_LINE_LOOP);
        glVertex3fv(v[index[4 * i + 0]]);
        glVertex3fv(v[index[4 * i + 1]]);
        glVertex3fv(v[index[4 * i + 2]]);
        glVertex3fv(v[index[4 * i + 3]]);
        glEnd();
    }
    
}


void display(){
    
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_LINE); /* flat shaded */
    gluQuadricNormals(qobj, GLU_SMOOTH);
    // Other Transformations
    // glTranslatef( 0.1, 0.0, 0.0 );      // Not included
    // glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included
    
    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    
    // Other Transformations
    // glScalef( 2.0, 2.0, 0.0 );          // Not included
    
    // Uncomment the object name
    glPushMatrix();
    glTranslated(0, 0.5, 0);
    glColor3f(1.0, 0.686, 0.067);
    sphere();
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, -0.5, 0);
    glRotatef(180, 1.0, 0.0, 0.0);
    sphere();
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, 0.1/2, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.337, 0.18, 0.078);
    gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 0.1/2, 0);
    glTranslated(0, -0.2, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.321, 0.247);
    gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 0.1/2, 0);
    glTranslated(0, 0.2, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.247, 1.0, 0.337);
    gluCylinder(qobj, 0.5, 0.5, 0.1, 30, 2);
    glPopMatrix();
    
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
    glutCreateWindow("Sphere");
    
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

