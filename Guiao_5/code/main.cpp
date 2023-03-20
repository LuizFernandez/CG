#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

GLfloat theta_i = 0, theta_o = 0;

void movimingTeaPot(){

	theta_i += 0.01;
	theta_o -= 0.01;

	glutPostRedisplay();

}

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void drawTree(){

	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.0f);
	glRotatef(-90, 1.0f, 0, 0);
	glutSolidCone(1.5, 5, 15, 15);
	glTranslatef(0.0f, 0.0f, 3.5f);
	glColor3f(0.2f, 0.6f, 0.0f);
	glutSolidCone(4.0f, 20.0f, 15, 15);
	glPopMatrix();

}

void drawScene(){

	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glColor3f(0.8f, 0.2f, 0.8f);
	glutSolidTorus(1, 2, 20, 20);
	glPopMatrix();

	float theta = (2 * M_PI) / 8;
	for(int i = 0; i < 8; i++){
		glPushMatrix();
		glTranslatef(15 * sin(theta * i + theta_i ), 2, 15 * cos(theta * i + theta_i));
		glRotatef(((theta * i  + theta_i)* 360) / (2 * M_PI) - 90, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glutSolidTeapot(1.5f);
		glPopMatrix();
	}

	float gama = (2* M_PI) / 16;
	for(int i = 0; i < 16; i++){
		glPushMatrix();
		glTranslatef(35 * sin(gama * i + theta_o), 2, 35 * cos(gama * i + theta_o));
		glRotatef(((gama * i + theta_o) * 360) / (2 * M_PI) + 90, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidTeapot(1.5f);
		glPopMatrix();
	}

	srand(658);
	for(int i = 0; i < 300; i++){
		glPushMatrix();
		float posx = 0, posz = 0;
		while(pow(posx,2) + pow(posz, 2) < pow(50, 2)){
			posx = (rand() % 200) - 100;
			posz = (rand() % 200) - 100;
		}
		glTranslatef(posx, 0.0, posz);
		drawTree();
		glPopMatrix();

	}

}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	// put code to draw scene in here
	drawScene();
	
	
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin\n");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutIdleFunc(movimingTeaPot);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
