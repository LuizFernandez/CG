

#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

unsigned int t, tw, th;
unsigned char* imageData;

int vertexCount;

GLfloat theta_i = 0, theta_o = 0;
GLuint *buffer, bufferCount;

int alpha = 10, beta = 10, r = 50;
int startX, startY, tracking = 0;

float k = 0.01;

float h(int i, int j){
	float x = imageData[i * tw + j];
	return x / 255 * 300;
}

// Interpolaçao Bilinear
float hf(float px, float pz){

	float x1 = floor(px);
	float z1 = floor(pz);
	float x2 = x1 + 1;
	float z2 = z1 + 1;

	float fz = pz - z1;

	float h_x1_z = h(x1, z1) * (1 - fz) + h(x1, z2) * fz;
	float h_x2_z = h(x2, z1) * (1 - fz) + h(x2, z2) * fz;

	float fx = px - x1;

	return (h_x1_z * (1 - fx) + h_x2_z * fx);
}

float camX = 00, camY = 30, camZ = 40;
float lX = 1, lY = camY, lZ = 1;

float dx = lX - camX, dy = lY - camY, dz = lZ - camZ;
float rx = (dy * 0 - 1 * dz), ry = (dx * 0 - 0 * dz), rz = (dx * 1 - 0 * dy);

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
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
    theta_i += 0.01;
	for(int i = 0; i < 8; i++){
		glPushMatrix();
		glTranslatef(15 * sin(theta * i + theta_i ), 2, 15 * cos(theta * i + theta_i));
		glRotatef(((theta * i  + theta_i)* 360) / (2 * M_PI) - 90, 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glutSolidTeapot(1.5f);
		glPopMatrix();
	}

	float gama = (2* M_PI) / 16;
    theta_o -= 0.01;
	for(int i = 0; i < 16; i++){
		glPushMatrix();
		glTranslatef(35 * sin(gama * i + theta_o), 2, 35 * cos(gama * i +  theta_o ));
		glRotatef(((gama * i +  theta_o ) * 360) / (2 * M_PI) + 90, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidTeapot(1.5f);
		glPopMatrix();
	}

	srand(100);
	for(int i = 0; i < 400; i++) {
        glPushMatrix();
        float posx = 0, posz = 0;
        while (pow(posx, 2) + pow(posz, 2) < pow(50, 2)) {
            posx = (rand() % 256) - 128;
            posz = (rand() % 256) - 128;
        }
        glTranslatef(posx, hf((posx + th / 2), (posz + tw / 2)), posz);
        drawTree();
        glPopMatrix();

    }

}

void drawTerrain() {

	for(int i = 0; i < th - 1; i++){
		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
	}

}


void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		      lX,lY,lZ,
			  0.0f,1.0f,0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	drawTerrain();
	drawScene();

// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {

	switch(key){
        case 'w':
            if(((camX + k * dx) + th/2) * tw + (camZ + k * dz) <= pow(255,2) && ((lX + k * dx ) + th/2) * tw + (lZ + k * dz) <= pow(255,2)){
                camX = camX + k * dx;
                camZ = camZ + k * dz;
                camY = 1.6 + hf(camX + th/2, camZ + tw/2);
                lX = lX + k * dx;
                lY = lY + k * dy;
                lZ = lZ + k * dz;
            }
			break;
		case 's':
            if(((camX - k * dx) + th/2) * tw + (camZ - k * dz) <= pow(255,2) && ((lX - k * dx ) + th/2) * tw + (lZ - k * dz) <= pow(255,2)) {
                camX = camX - k * dx;
                camZ = camZ - k * dz;
                camY = 1.6 + hf(camX + th/2, camZ + tw/2);
                lX = camX + dx;
                lY = camY + dy;
                lZ = camZ + dz;
            }
			break;
		case 'a':
            if(((camX + k * dx) + th/2) * tw + (camZ + k * dz) <= pow(255,2) && ((lX + k * dx ) + th/2) * tw + (lZ + k * dz) <= pow(255,2)) {
                camX = camX - k * rx;
                camZ = camZ - k * rz;
                camY = 1.6 + hf(camX + th/2, camZ + tw/2);
                lX = lX - k * rx;
                lY = lY - k * ry;
                lZ = lZ - k * rz;
            }
			break;
		case 'd':
            if(((camX - k * dx) + th/2) * tw + (camZ - k * dz) <= pow(255,2) && ((lX - k * dx ) + th/2) * tw + (lZ - k * dz) <= pow(255,2)) {
                camX = camX + k * rx;
                camZ = camZ + k * rz;
                camY = 1.6 + hf(camX + th/2, camZ + tw/2);
                lX = lX + k * rx;
                lY = lY + k * ry;
                lZ = lZ + k * rz;
            }
			break;
		default:
			break;
	}

}

void processMouseButtons(int button, int state, int xx, int yy) {

	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}

}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {

        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }

    lX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    lZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    lY = rAux * 							      sin(betaAux * 3.14 / 180.0);
    dx = lX - camX;
    dy = lY - camY;
    dz = lZ - camZ;
    rx = (dy * 0 - 1 * dz);
    ry = (dx * 0 - 0 * dz);
    rz = (dx * 1 - 0 * dy);
}


void init() {

    ilInit();

	// 	Load the height map "terreno.jpg"
	ilGenImages(1, &t);
	ilBindImage(t);
	// terreno.jpg is the image containing our height map
	ilLoadImage((ILstring)"terreno.jpg");
	// convert the image to single channel per pixel
	// with values ranging between 0 and 255
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
	// important: check tw and th values
	// both should be equal to 256
	// if not there was an error loading the image
	// most likely the image could not be found
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
    printf("t: %d;\n", t);
	printf("th:%d; tw:%d\n", th, tw);
	// imageData is a LINEAR array with the pixel values
	imageData = ilGetData();

	// 	Build the vertex arrays
	buffer = (GLuint *)calloc(th-1, sizeof(GLuint));
	glGenBuffers(th-1, buffer);

	int halfW = tw / 2;
	int halfH = th / 2;

	vertexCount = tw * 2;

	for(int i = 0; i < th - 1; i++){
		std::vector<float> vertex;
		for(int j = 0; j < tw; j++){
			vertex.push_back(i - halfH);
			vertex.push_back(h(i, j));
			vertex.push_back(j - halfW);

			vertex.push_back(i + 1 - halfH);
			vertex.push_back(h(i + 1, j));
			vertex.push_back(j - halfW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(float) * vertex.size(),
					 vertex.data() ,
					 GL_STATIC_DRAW);

	}


	// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG@DI-UM");
		

// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	init();	

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

