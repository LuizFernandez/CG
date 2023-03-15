#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

float posx = 0, posz = 0, angle = 0, scale = 1;

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

	// put axis drawing in here
	glBegin(GL_LINES);
		// Eixo dos x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Eixo dos y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Eixo dos z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();


	// put the geometric transformations here
	glTranslated(posx, 0.0, posz);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glScalef(scale, scale, scale);


	// put pyramid drawing instructions here
	glBegin(GL_TRIANGLES);

		// Base
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		//Lados
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);


	glEnd();



	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void object_update(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			posz -= 0.1;
			break;
		case 's':
			posz += 0.1;
			break;
		case 'a' :
			posx -= 0.1;
			break;
		case 'd' : 
			posx += 0.1;
			break;
		case 'l':
			angle += 15;
			break;
		case 'r':
			angle -= 15;
			break;
		case 'z':
			scale += 0.1;
			break;
		case 'x':
			scale -= 0.1;
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
	glutKeyboardFunc(object_update);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
