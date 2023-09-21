#include "CallBack.h"
#include "Header.h"

int squrecount = 1;
float squresize = 0.1f;
GLfloat squre1[7];
GLfloat squre2[7];
GLfloat squre3[7];
GLfloat squre4[7];
GLfloat squre5[7];


GLvoid drawScene() {
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(squre1[4], squre1[5], squre1[6]);
	glRectf(squre1[0], squre1[1], squre1[2], squre1[3]);

	glColor3f(squre2[4], squre2[5], squre2[6]);
	glRectf(squre2[0], squre2[1], squre2[2], squre2[3]);

	glColor3f(squre3[4], squre3[5], squre3[6]);
	glRectf(squre3[0], squre3[1], squre3[2], squre3[3]);

	glColor3f(squre4[4], squre4[5], squre4[6]);
	glRectf(squre4[0], squre4[1], squre4[2], squre4[3]);

	glColor3f(squre5[4], squre5[5], squre5[6]);
	glRectf(squre5[0], squre5[1], squre5[2], squre5[3]);
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
GLvoid Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / 400.0) - 1;
	float ogy = -(((float)y / 400.0) - 1);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		switch (squrecount) {
		case 1:
			squre1[0] = ogx - squresize;
			squre1[1] = ogy - squresize;
			squre1[2] = ogx + squresize;
			squre1[3] = ogy + squresize;
			squre1[4] = (rand() % 10 / 10.0);
			squre1[5] = (rand() % 10 / 10.0);
			squre1[6] = (rand() % 10 / 10.0);
			break;
		case 2:
			squre2[0] = ogx - squresize;
			squre2[1] = ogy - squresize;
			squre2[2] = ogx + squresize;
			squre2[3] = ogy + squresize;
			squre2[4] = (rand() % 10 / 10.0);
			squre2[5] = (rand() % 10 / 10.0);
			squre2[6] = (rand() % 10 / 10.0);
			break;
		case 3:
			squre3[0] = ogx - squresize;
			squre3[1] = ogy - squresize;
			squre3[2] = ogx + squresize;
			squre3[3] = ogy + squresize;
			squre3[4] = (rand() % 10 / 10.0);
			squre3[5] = (rand() % 10 / 10.0);
			squre3[6] = (rand() % 10 / 10.0);
			break;
		case 4:
			squre4[0] = ogx - squresize;
			squre4[1] = ogy - squresize;
			squre4[2] = ogx + squresize;
			squre4[3] = ogy + squresize;
			squre4[4] = (rand() % 10 / 10.0);
			squre4[5] = (rand() % 10 / 10.0);
			squre4[6] = (rand() % 10 / 10.0);
			break;
		case 5:
			squre5[0] = ogx - squresize;
			squre5[1] = ogy - squresize;
			squre5[2] = ogx + squresize;
			squre5[3] = ogy + squresize;
			squre5[4] = (rand() % 10 / 10.0);
			squre5[5] = (rand() % 10 / 10.0);
			squre5[6] = (rand() % 10 / 10.0);
			break;
		}
		squrecount++;
		glutDisplayFunc(drawScene);
	}
}