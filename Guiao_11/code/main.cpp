#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include <cmath>

// distance to target
float dist = 700;
// distance between the eyes
float disp = 30;

float camX = 0, camY = 0, camZ = 500;
float lX = 0.0, lY = 0, lZ = -500;
float delta = 100;
float k = 0.01;

float up[3] = {0.0, 1.0, 0.0};
float r[3] = {0.0, 0.0, 0.0};
float l[3] = {lX - camX, lY - camY, lZ - camZ};

float pos[3] = {camX, camY, camZ};


float angle=0;
float cBlack[] = {0,0,0,0};
float cWhite[] = {1,1,1,1};
float cRed[] = {0.4,0,0};
float cGreen[] = {0,0.4,0.4};
float cRedish[] = {0.2,0,0};
float cGreenish[] = {0,0.2,0.2};

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;

}

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,400,10000);
	glMatrixMode(GL_MODELVIEW);
}

void calcPoint( float* res, unsigned char signal){

    switch (signal) {
        case '+':
            res[0] = pos[0] + r[0] * delta;
            res[1] = pos[1] + r[1] * delta;
            res[2] = pos[2] + r[2] * delta;
            break;
        case '-':
            res[0] = pos[0] - r[0] * delta;
            res[1] = pos[1] - r[1] * delta;
            res[2] = pos[2] - r[2] * delta;
            break;
    }
}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float lpos[] = {1,1,0,0};

	// teapot size
	float ts = 150;
    float camR[3] = {0.0, 0.0, 0.0};
    float camL[3] = {0.0, 0.0, 0.0};

    calcPoint( camR, '+');
    calcPoint( camL, '-');

	// fill in the code...
    glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
    // set camera for red eye
    glLoadIdentity();
    gluLookAt(camR[0], camR[1], camR[2],
              lX, lY, lZ,
              0.0, 1.0, 0.0);

    // draw scene
    glutWireTeapot(ts);

    glClear(GL_DEPTH_BUFFER_BIT);
    glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
    // ser camera for blue eye.
    glLoadIdentity();
    gluLookAt(camL[0], camL[1], camL[2],
              lX, lY, lZ,
              0.0f, 1.0f, 0.0f);

    // draw scene
    glutWireTeapot(ts);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glutSwapBuffers();

}

void processNormalKeys(unsigned char key, int x, int y) {

	char s[20];
	if (key == 27) 
		exit(0);
	switch(key) {
        case 'w' :
            camX = camX + k * l[0];
            camZ = camZ + k * l[2];
            lX = lX + k * l[0];
            lZ = lZ + k * l[2];
            break;
        case 's' :
            dist *= 1.1;
            camX = camX - k * l[0];
            camZ = camZ - k * l[2];
            lX = lX - k * l[0];
            lZ = lZ - k * l[2];
            break;
		case 'a' :
            dist *=.9;
            camX = camX - k * r[0];
            camZ = camZ - k * r[2];
            lX = lX - k * r[0];
            lZ = lZ - k * r[2];
            break;
        case 'd':
            camX = camX + k * r[0];
            camZ = camZ + k * r[2];
            lX = lX + k * r[0];
            lZ = lZ + k * r[2];
            break;
	}
    pos[0] = camX;
    pos[1] = camY;
    pos[2] = camZ;
    l[0] = lX - camX;
    l[1] = lY - camY;
    l[2] = lZ - camZ;
	sprintf(s,"%f", dist);
	glutSetWindowTitle(s);

}


int main(int argc, char **argv) {

    normalize(up);
    normalize(l);

    cross(l, up, r);
    normalize(r);

	// GLUT and window init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG @ DI");

	// GLUT callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	
	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f,0.0f,0.0f,0.0f);


	glutMainLoop();

	return 0;
}

