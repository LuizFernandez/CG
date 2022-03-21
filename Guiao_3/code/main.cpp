#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.5f, radius = 50.0f;
float camX, camY, camZ;

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
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


void drawCylinder(float radius, float height, int slices) { //Ver como mudar de cor cada fatia

	float angles = (M_PI*2) / slices;
	float posy = height / 2;
	float colordes = 1 / slices;
	float color = 1;

	glBegin(GL_TRIANGLES);
	for(int i = 0; i < slices; i++){
		glColor3f(0.0, color, 0.0);

		//Base
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0,-posy,0.0);
			glVertex3f(cos(angles*i) * radius, -posy, sin(angles*i) * radius);
			glVertex3f(cos(angles*(i+1)) * radius, -posy, sin(angles*(i+1))*radius);
		glEnd();

		//Topo
		glBegin(GL_TRIANGLES);
			glVertex3f(0.0,posy,0.0);
			glVertex3f(cos(angles*(i+1)) * radius, posy, sin(angles*(i+1))*radius);
			glVertex3f(cos(angles*i) * radius, posy, sin(angles*i) * radius);
		glEnd();

		//Lateral
		glBegin(GL_QUADS);
			glVertex3f(cos(angles*i) * radius, -posy, sin(angles*i) * radius);
			glVertex3f(cos(angles*i) * radius, posy, sin(angles*i) * radius);
			glVertex3f(cos(angles*(i+1)) * radius, posy, sin(angles*(i+1))*radius);
			glVertex3f(cos(angles*(i+1)) * radius, -posy, sin(angles*(i+1))*radius);
		glEnd();
		
		color -= colordes;
	}

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {

	switch(key){
		case GLUT_KEY_RIGHT:
			alfa -= 0.1;
			break;
		case GLUT_KEY_LEFT:
			alfa += 0.1;
			break;
		case GLUT_KEY_UP:
			beta += 0.1;
			if(beta > 1.5f)
				beta = 1.5f;
			break;
		case GLUT_KEY_DOWN:
			beta -= 0.1;
			if(beta < -1.5f)
				beta = -1.5f;
			break;
		case GLUT_KEY_PAGE_UP:
			radius += 1.0f;
			break;
		case GLUT_KEY_PAGE_DOWN:
			radius -= 1.0f;
			if(radius < 1.0f)
				radius = 1.0f;
			break;
	}
	spherical2Cartesian();
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
	
// Callback registration for keyboard processing
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
