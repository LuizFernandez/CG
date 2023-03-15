#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

GLfloat beta = 0, alpha = 0;

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


void drawCylinder(float radius, float height, int slices) {

	float alpha = (2 * M_PI) / slices; 
	float lower_height = -height/2;
	float higher_height = height/2;

	for(int i = 0; i < slices; i++){

		float ang = alpha * i;
		float next_ang = alpha * (i + 1);
		float xx_1 = radius * sin(ang);
		float zz_1 = radius * cos(ang);
		float xx_2 = radius * sin(next_ang);
		float zz_2 = radius * cos(next_ang);

		// Draw Lower Base
		glColor3f(0.0f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLES);
			glVertex3f(xx_1, lower_height, zz_1);
			glVertex3f(0.0f, lower_height, 0.0f);
			glVertex3f(xx_2, lower_height, zz_2);
		glEnd();

		// Draw Side
		glColor3f(0.5f, 0.5f, 0.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(xx_1, lower_height, zz_1);
			glVertex3f(xx_2, lower_height, zz_2);
			glVertex3f(xx_1, higher_height, zz_1);
		glEnd();
		glColor3f(0.0f, 0.5f, 0.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(xx_2, higher_height, zz_2);
			glVertex3f(xx_1, higher_height, zz_1);
			glVertex3f(xx_2, lower_height, zz_2);
		glEnd();

		// Draw Upper Base
		glColor3f(0.5f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, higher_height, 0.0f);
			glVertex3f(xx_1, higher_height, zz_1);
			glVertex3f(xx_2, higher_height, zz_2);
		glEnd();
	}

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5 * cos(beta) * sin(alpha), 5 * sin(beta), 5 * cos(beta) * cos(alpha), 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawCylinder(1,2,20);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	switch (c){
		case 'l':
			alpha -= (M_PI) / 16;
			break;
		case 'r':
			alpha += (M_PI) / 16;
			break;
		case 'u':
			if ((beta + (M_PI) / 16 ) < M_PI / 2)
				beta += (M_PI) / 16;
			else
				beta = M_PI / 2;
			break;
		case 'd':
			if ((beta - (M_PI) / 16 ) > -(M_PI / 2))
				beta -= (M_PI) / 16;
			else 
				beta = -(M_PI / 2);
			break;
		default:
			break;
	}

	glutPostRedisplay();

}


void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

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
	glPolygonMode(GL_FRONT, GL_LINE);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
