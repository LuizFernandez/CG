#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

float posx = 0, posz = 0, angle = 0, scalex = 1, scaley = 1, scalez = 1;

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
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	//Sistemas de Coordenadas
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

// put the geometric transformations here

	glTranslatef(posx,0.0,posz);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(scalex, scaley, scalez);

// put drawing instructions here

	glBegin(GL_TRIANGLES);

		//Base
		glColor3ub(75,0,130);
		glVertex3f(-0.5,0.0,-0.5);
		glVertex3f(0.5,0.0,-0.5);
		glVertex3f(0.5,0.0,0.5);
		
		glColor3ub(0,0,255);
		glVertex3f(0.5,0.0,0.5);
		glVertex3f(-0.5,0.0,0.5);
		glVertex3f(-0.5,0.0,-0.5);

		//Lados
		glColor3ub(0,128,0);
		glVertex3f(-0.5,0.0,-0.5);
		glVertex3f(0.0,1,0.0);
		glVertex3f(0.5,0,-0.5);

		glColor3ub(255,255,0);
		glVertex3f(0.5,0,-0.5);
		glVertex3f(0.0,1,0.0);
		glVertex3f(0.5,0,0.5);

		glColor3ub(0,128,0);
		glVertex3f(0.5,0,0.5);
		glVertex3f(0.0,1,0.0);
		glVertex3f(-0.5,0,0.5);

		glColor3ub(255,255,0);
		glVertex3f(-0.5,0,0.5);
		glVertex3f(0.0,1,0.0);
		glVertex3f(-0.5,0,-0.5);

	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

void keyBoard(unsigned char key, int x, int y){
	switch (key) {
	case 'w':
		posx -= 0.1;
		break;
	case 'd':
		posz -= 0.1;
		break;
	case 'a':
		posz += 0.1;
		break;
	case 's':
		posx += 0.1;
		break;
	case 'e':
		angle -= 10;
		break;
	case 'r':
		angle += 10;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void keyBoardSpecial(int key_code, int x, int y){
	switch (key_code) {
		case GLUT_KEY_UP:
			scalex++;
			scaley++;
			scalez++;
			break;
		case GLUT_KEY_DOWN:
			scalex--;
			scaley--;
			scalez--;
			break;
		default:
			break;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks

	glutKeyboardFunc(keyBoard);
	glutSpecialFunc(keyBoardSpecial);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}