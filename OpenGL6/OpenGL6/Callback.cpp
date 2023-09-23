#include "Header.h"
#include "CallBack.h"

float squre[5][7];
float divsqure1[4][7];
float divsqure2[4][7];
float divsqure3[4][7];
float divsqure4[4][7];
float divsqure5[4][7];
float rectsize = 0.1;
int squreindx;

bool sqr1stop = false;
bool sqr2stop = false;

GLvoid defrect() {
	for (int i = 0; i < 5; i++) {
		float ranx = (((rand() % 19) + 1) / 10.0) - 1;
		float rany = (((rand() % 19) + 1) / 10.0) - 1;
		squre[i][0] = ranx - rectsize;
		squre[i][1] = rany - rectsize;
		squre[i][2] = ranx + rectsize;
		squre[i][3] = rany + rectsize;
		for (int j = 4; j < 7; j++) {
			squre[i][j] = ((rand() % 10)) / 10.0;
		}
	}
}
GLvoid drawScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 5; i++) {
		glColor3f(squre[i][4], squre[i][5], squre[i][6]);
		glRectf(squre[i][0], squre[i][1], squre[i][2], squre[i][3]);
	}
	for (int i = 0; i < 4; i++) {
		glColor3f(divsqure1[i][4], divsqure1[i][5], divsqure1[i][6]);
		glRectf(divsqure1[i][0], divsqure1[i][1], divsqure1[i][2], divsqure1[i][3]);
	}
	for (int i = 0; i < 4; i++) {
		glColor3f(divsqure2[i][4], divsqure2[i][5], divsqure2[i][6]);
		glRectf(divsqure2[i][0], divsqure2[i][1], divsqure2[i][2], divsqure2[i][3]);
	}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
GLvoid Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	//squre0 ³ª´©±â
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre[0][0] && ogx <squre[0][2] && ogy >squre[0][1] && ogy < squre[0][3]) {
		squreindx = 0;
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				divsqure1[i][0] = squre[0][0];
				divsqure1[i][1] = squre[0][1];
				divsqure1[i][2] = squre[0][2] - rectsize;
				divsqure1[i][3] = squre[0][3] - rectsize;
				divsqure1[i][4] = squre[0][4];
				divsqure1[i][5] = squre[0][5];
				divsqure1[i][6] = squre[0][6];
				break;
			case 1:
				divsqure1[i][0] = squre[0][0] + rectsize;
				divsqure1[i][1] = squre[0][1];
				divsqure1[i][2] = squre[0][2];
				divsqure1[i][3] = squre[0][3] - rectsize;
				divsqure1[i][4] = squre[0][4];
				divsqure1[i][5] = squre[0][5];
				divsqure1[i][6] = squre[0][6];
				break;
			case 2:
				divsqure1[i][0] = squre[0][0];
				divsqure1[i][1] = squre[0][1]+rectsize;
				divsqure1[i][2] = squre[0][2]-rectsize;
				divsqure1[i][3] = squre[0][3];
				divsqure1[i][4] = squre[0][4];
				divsqure1[i][5] = squre[0][5];
				divsqure1[i][6] = squre[0][6];
				break;
			case 3:
				divsqure1[i][0] = squre[0][0] + rectsize;
				divsqure1[i][1] = squre[0][1] + rectsize;
				divsqure1[i][2] = squre[0][2];
				divsqure1[i][3] = squre[0][3];
				divsqure1[i][4] = squre[0][4];
				divsqure1[i][5] = squre[0][5];
				divsqure1[i][6] = squre[0][6];
				break;
			}
		}

		squre[0][0] = -10;
		squre[0][1] = -10;
		squre[0][2] = -10;
		squre[0][3] = -10;
		sqr1stop = true;
		glutTimerFunc(10, Timer, 0);
	}
	//squre1 ³ª´©±â
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre[1][0] && ogx <squre[1][2] && ogy >squre[1][1] && ogy < squre[1][3]) {
		squreindx = 1;
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				divsqure2[i][0] = squre[1][0];
				divsqure2[i][1] = squre[1][1];
				divsqure2[i][2] = squre[1][2] - rectsize;
				divsqure2[i][3] = squre[1][3] - rectsize;
				divsqure2[i][4] = squre[1][4];
				divsqure2[i][5] = squre[1][5];
				divsqure2[i][6] = squre[1][6];
				break;
			case 1:
				divsqure2[i][0] = squre[1][0] + rectsize;
				divsqure2[i][1] = squre[1][1];
				divsqure2[i][2] = squre[1][2];
				divsqure2[i][3] = squre[1][3] - rectsize;
				divsqure2[i][4] = squre[1][4];
				divsqure2[i][5] = squre[1][5];
				divsqure2[i][6] = squre[1][6];
				break;
			case 2:
				divsqure2[i][0] = squre[1][0];
				divsqure2[i][1] = squre[1][1] + rectsize;
				divsqure2[i][2] = squre[1][2] - rectsize;
				divsqure2[i][3] = squre[1][3];
				divsqure2[i][4] = squre[1][4];
				divsqure2[i][5] = squre[1][5];
				divsqure2[i][6] = squre[1][6];
				break;
			case 3:
				divsqure2[i][0] = squre[1][0] + rectsize;
				divsqure2[i][1] = squre[1][1] + rectsize;
				divsqure2[i][2] = squre[1][2];
				divsqure2[i][3] = squre[1][3];
				divsqure2[i][4] = squre[1][4];
				divsqure2[i][5] = squre[1][5];
				divsqure2[i][6] = squre[1][6];
				break;
			}
		}
		squre[1][0] = -11;
		squre[1][1] = -11;
		squre[1][2] = -11;
		squre[1][3] = -11;
		sqr2stop = true;
		glutTimerFunc(10, Timer2, 0);
	}
}
//squre0 ¼Ò¸ê
GLvoid Timer(int value) {
	float move = 0.0005;
	if (sqr1stop==true) {
		for (int i = 0; i < 4; i++) {
			if (divsqure1[i][0] >= divsqure1[i][2]) {
				divsqure1[i][0] = -10;
				divsqure1[i][1] = -10;
				divsqure1[i][2] = -10;
				divsqure1[i][3] = -10;
				sqr1stop = false;
			}
			switch (i) {
			case 0:
				divsqure1[i][0] -= move;
				divsqure1[i][1] -= move;
				divsqure1[i][2] -= move * 2;
				divsqure1[i][3] -= move * 2;
				break;
			case 1:
				divsqure1[i][0] += move * 2;
				divsqure1[i][1] -= move;
				divsqure1[i][2] += move;
				divsqure1[i][3] -= move * 2;
				break;
			case 2:
				
				divsqure1[i][0] -= move;
				divsqure1[i][1] += move * 2;
				divsqure1[i][2] -= move * 2;
				divsqure1[i][3] += move;
				break;
			case 3:
				divsqure1[i][0] += move * 2;
				divsqure1[i][1] += move * 2;
				divsqure1[i][2] += move;
				divsqure1[i][3] += move;
				break;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
	}
	
}

//squre1 ¼Ò¸ê
GLvoid Timer2(int value) {
	float move = 0.0005;
	if (sqr2stop == true) {
		for (int i = 0; i < 4; i++) {
			if (divsqure2[i][0] >= divsqure2[i][2]) {
				divsqure2[i][0] = -10;
				divsqure2[i][1] = -10;
				divsqure2[i][2] = -10;
				divsqure2[i][3] = -10;
				sqr2stop = false;
			}
			switch (i) {
			case 0:
				divsqure2[i][0] -= move;
				divsqure2[i][1] -= move;
				divsqure2[i][2] -= move * 2;
				divsqure2[i][3] -= move * 2;
				break;
			case 1:
				divsqure2[i][0] += move * 2;
				divsqure2[i][1] -= move;
				divsqure2[i][2] += move;
				divsqure2[i][3] -= move * 2;
				break;
			case 2:

				divsqure2[i][0] -= move;
				divsqure2[i][1] += move * 2;
				divsqure2[i][2] -= move * 2;
				divsqure2[i][3] += move;
				break;
			case 3:
				divsqure2[i][0] += move * 2;
				divsqure2[i][1] += move * 2;
				divsqure2[i][2] += move;
				divsqure2[i][3] += move;
				break;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer2, 1);
	}
}