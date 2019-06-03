#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>

GLuint texture[2];

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;


int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width

    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }

    //printf("Width of %s: %lu\n", filename, image->sizeX);
    // read the height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }

    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }

    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    // read the bitsperpixel

    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }

    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }

    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);
    // read the data.
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }
    // we're done.
    return 1;

}


Image * loadTexture(){
    Image *image1;
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));

    if (image1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }

    if (!ImageLoad("/Users/zhangyuan/Desktop/plane.bmp", image1)) {
        exit(1);
    }
    return image1;

}

void light(void)
{
    GLfloat position[]={3.0f,30.0f,3.0f,1.0f};
    GLfloat ambient[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat diffuse[]={0.0f, 0.8f, 0.8f, 1.0f};
    GLfloat specular[]={0.0f, 0.6f, 0.6f, 1.0f};

    glLightfv(GL_POSITION,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

void draw_plane(float x, float z)
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    // glNormal3f(-x, 0, -z);
    glVertex3f(-x, 0, -z);

    glTexCoord2f(0.0, 1.0);
    // glNormal3f(x, 0, -z);
    glVertex3f(x, 0, -z);

    glTexCoord2f(1.0, 1.0);
    // glNormal3f(x, 0, z);
    glVertex3f(x, 0, z);

    glTexCoord2f(1.0, 0.0);
    // glNormal3f(-x, 0, z);
    glVertex3f(-x, 0, z);

    glEnd();
}

void draw_board(float x, float y) {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(-x, 0, 0);
    glVertex3f(-x, 0, 0);
    glNormal3f(x, 0, 0);
    glVertex3f(x, 0, 0);
    glNormal3f(x, y, 0);
    glVertex3f(x, y, 0);
    glNormal3f(-x, y, 0);
    glVertex3f(-x, y, 0);
    glEnd();
}

void draw_curve_board(float x, float low_y, float high_y) {
    glBegin(GL_POLYGON);
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(-x, 0, 0);
    glVertex3f(-x, 0, 0);
    glNormal3f(x, 0, 0);
    glVertex3f(x, 0, 0);
    glNormal3f(x, low_y, 0);
    glVertex3f(x, low_y, 0);
    glNormal3f(x/2, high_y, 0);
    glVertex3f(x/2, high_y, 0);
    glNormal3f(-x/2, high_y, 0);
    glVertex3f(-x/2, high_y, 0);
    glNormal3f(-x, low_y, 0);
    glVertex3f(-x, low_y, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(-x/2, high_y, 0);
    glVertex3f(-x/2, high_y, 0);
    glNormal3f(x/2, high_y, 0);
    glVertex3f(x/2, high_y, 0);
    glNormal3f(x/2, high_y, 0.05);
    glVertex3f(x/2, high_y, 0.05);
    glNormal3f(-x/2, high_y, 0.05);
    glVertex3f(-x/2, high_y, 0.05);
    glEnd();
}

void plate() {
    glPushMatrix();
    glRotatef(45, 1.0, 1.0, 0.5);
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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Image *image1 = loadTexture();
    if(image1 == NULL){
        printf("Image was not returned from loadTexture\n");
        exit(0);
    }

    // Create Texture

    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture

    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,

                 GL_RGB, GL_UNSIGNED_BYTE, image1->data);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_FLAT);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    plate();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5*(GLfloat)h / (GLfloat)w, 1.5*(GLfloat)h / (GLfloat)w, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    light();


    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
