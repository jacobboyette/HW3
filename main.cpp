#include <math.h>
#include "GL/glut.h"

GLsizei ww = 512;
GLsizei wh = 512;
GLfloat left, right, bottom, top, near, far;
const float REGION_DIM = 4;
const GLfloat DtoR = 0.017453;
GLfloat theta = 0, phi = 90, rho = 20;
GLfloat dTheta = 5, dPhi = 5, dRho = 0.5;
GLfloat direction = 1.0;
GLfloat a = 0, b = 0, c = 0;
GLfloat d = 1;

void display(void);
void init(void);
void reshape(GLsizei w, GLsizei h);
void keys(unsigned char k, int x, int y);
void specialKeys(int k, int x, int y);
void cube(float x, float y, float z, float size);

void cube(float x, float y, float z, float size) {

	float halpSize = size / 2;
	float v1[3] = { x - halpSize, y - halpSize, z - halpSize };
	float v2[3] = { x - halpSize, y + halpSize, z - halpSize };
	float v3[3] = { x - halpSize, y + halpSize, z + halpSize };
	float v4[3] = { x - halpSize, y - halpSize, z + halpSize };
	float v5[3] = { x + halpSize, y - halpSize, z - halpSize };
	float v6[3] = { x + halpSize, y + halpSize, z - halpSize };
	float v7[3] = { x + halpSize, y + halpSize, z + halpSize };
	float v8[3] = { x + halpSize, y - halpSize, z + halpSize };

	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v4);
	glVertex3fv(v3);
	glVertex3fv(v2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(v2);
	glVertex3fv(v3);
	glVertex3fv(v7);
	glVertex3fv(v6);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(v3);
	glVertex3fv(v4);
	glVertex3fv(v8);
	glVertex3fv(v7);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v5);
	glVertex3fv(v8);
	glVertex3fv(v4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v6);
	glVertex3fv(v5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(v5);
	glVertex3fv(v6);
	glVertex3fv(v7);
	glVertex3fv(v8);
	glEnd();

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(rho * sin(theta * DtoR) * sin(phi * DtoR), rho * cos(phi * DtoR), rho * cos(theta * DtoR) * sin(phi * DtoR), 0, 0, 0, 0, 1, 0);

	//----------- the cube --------------------------
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 0, 0);
	cube(a, b, c, d * 1.3);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1, 1, 0);
	cube(a, b, c, d * 1.3);

	//----------- the teapot --------------------------
	glPushMatrix(); // Save the current matrix
	glTranslatef(a, b + d, c); // Translate to the top of the cube
	glColor3f(0, 1, 1); // Set teapot color
	glutSolidTeapot(d / 2); // Draw the teapot. adjust the size if needed.
	glPopMatrix(); // Restore the saved matrix

	//----------- the teapot (line) --------------------------
	glPushMatrix();
	glTranslatef(a, b + d, c);
	glColor3f(0, 0, 0); // Different color for line view
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Line mode
	glutSolidTeapot(d / 2);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();

}

void init(void)
{
	float ratio = ww * 1.0 / (wh * 1.0);

	glClearColor(0.8, 0.8, 0.8, 1.0);	// background color; default black; (R, G, B, Opacity)
	glColor3f(0, 1, 1);	// drawing color; default white

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	near = REGION_DIM * 4;
	far = REGION_DIM * 20;

	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
}

void reshape(GLsizei w, GLsizei h)
{
	float ratio = w * 1.0 / (h * 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ratio >= 1)
	{
		left = -1.0 * REGION_DIM * ratio;
		right = REGION_DIM * ratio;
		bottom = -1.0 * REGION_DIM;
		top = REGION_DIM;
	}
	else
	{
		left = -1.0 * REGION_DIM;
		right = REGION_DIM;
		bottom = -1.0 * REGION_DIM / ratio;
		top = REGION_DIM / ratio;
	}

	near = REGION_DIM * 4;
	far = REGION_DIM * 20;

	glFrustum(left, right, bottom, top, near, far);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);		// important!

	//------ reset the window size
	ww = w;
	wh = h;
}

void keys(unsigned char k, int x, int y) {

	if (k == '+')
		rho -= dRho;
	else if (k == '-')
		rho += dRho;
	else if (k == 'p')
		direction = 1.0;
	else if (k == 'n')
		direction = -1.0;
	else if (k == 'a' || k == 'A')
		a += 0.1 * direction;
	else if (k == 'b' || k == 'B')
		b += 0.1 * direction;
	else if (k == 'c' || k =='C')
		c += 0.1 * direction;
	else if (k == 'd' || k == 'D')
		d += 0.1 * direction;
	else if (k == 'R' || k == 'r') {
		theta = 0; phi = 90; rho = 20;
	}
}

void specialKeys(int k, int x, int y) {

	if (k == GLUT_KEY_LEFT) {
		theta -= dTheta;

		if (theta < -360)
			theta += 360;
	}
	else if (k == GLUT_KEY_RIGHT) {
		theta += dTheta;

		if (theta > 360)
			theta -= 360;
	}
	else if (k == GLUT_KEY_UP) {
		phi -= dPhi;

		if (phi < -360)
			phi += 360;
	}
	else if (k == GLUT_KEY_DOWN) {
		phi += dPhi;

		if (phi > 360)
			phi -= 360;
	}
}

	void mouse(int button, int state, int x, int y){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			direction = 1.0;
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			direction = -1.0;
		}
	}

	int main(int argc, char** argv) {  // Add argc and argv parameters!
		glutInit(&argc, argv);  // ✅ Initialize GLUT
	
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Enable double buffering and depth testing
		glutInitWindowSize(ww, wh);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Jacob Boyette");  
	
		init();  // Initialize OpenGL settings
	
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(keys);
		glutSpecialFunc(specialKeys);
		glutMouseFunc(mouse);
	
		glutMainLoop();  // Start the event loop
		return 0;
	}
	

	
