#include "Header.h"
#include "CallBack.h"

float squre[5][7];
float divsqure[4][7];
float rectsize = 0.1;
int squreindx;

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
		glColor3f(divsqure[i][4], divsqure[i][5], divsqure[i][6]);
		glRectf(divsqure[i][0], divsqure[i][1], divsqure[i][2], divsqure[i][3]);
	}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
GLvoid Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre[0][0] && ogx <squre[0][2] && ogy >squre[0][1] && ogy < squre[0][3]) {
		squreindx = 0;
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				divsqure[i][0] = squre[0][0];
				divsqure[i][1] = squre[0][1];
				divsqure[i][2] = squre[0][2] - rectsize;
				divsqure[i][3] = squre[0][3] - rectsize;
				divsqure[i][4] = squre[0][4];
				divsqure[i][5] = squre[0][5];
				divsqure[i][6] = squre[0][6];
				break;
			case 1:
				divsqure[i][0] = squre[0][0] + rectsize;
				divsqure[i][1] = squre[0][1];
				divsqure[i][2] = squre[0][2];
				divsqure[i][3] = squre[0][3] - rectsize;
				divsqure[i][4] = squre[0][4];
				divsqure[i][5] = squre[0][5];
				divsqure[i][6] = squre[0][6];
				break;
			case 2:
				divsqure[i][0] = squre[0][0];
				divsqure[i][1] = squre[0][1]+rectsize;
				divsqure[i][2] = squre[0][2]-rectsize;
				divsqure[i][3] = squre[0][3];
				divsqure[i][4] = squre[0][4];
				divsqure[i][5] = squre[0][5];
				divsqure[i][6] = squre[0][6];
				break;
			case 3:
				divsqure[i][0] = squre[0][0] + rectsize;
				divsqure[i][1] = squre[0][1] + rectsize;
				divsqure[i][2] = squre[0][2];
				divsqure[i][3] = squre[0][3];
				divsqure[i][4] = squre[0][4];
				divsqure[i][5] = squre[0][5];
				divsqure[i][6] = squre[0][6];
				break;
			}
		}

		squre[0][0] = -10;
		squre[0][1] = -10;
		squre[0][2] = -10;
		squre[0][3] = -10;
	}
	glutTimerFunc(10, Timer, 1);
	glutPostRedisplay();
}
GLvoid Timer(int value) {
	float move = 0.0001;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			if (divsqure[i][0] >= divsqure[i][2]) {
				divsqure[i][0] = -10;
				divsqure[i][1] = -10;
				divsqure[i][2] = -10;
				divsqure[i][3] = -10;
			}
			else {
				divsqure[i][0] -= move;
				divsqure[i][1] -= move;
				divsqure[i][2] -= move * 2;
				divsqure[i][3] -= move * 2;
			}
			break;
		case 1:
			if (divsqure[i][0] >= divsqure[i][2]) {
				divsqure[i][0] = -10;
				divsqure[i][1] = -10;
				divsqure[i][2] = -10;
				divsqure[i][3] = -10;
			}
			else{
				divsqure[i][0] += move*2;
				divsqure[i][1] -= move;
				divsqure[i][2] += move;
				divsqure[i][3] -= move*2;
			}
			break;
		case 2:
			if (divsqure[i][0] >= divsqure[i][2]) {
				divsqure[i][0] = -10;
				divsqure[i][1] = -10;
				divsqure[i][2] = -10;
				divsqure[i][3] = -10;
			}
			else{
				divsqure[i][0] -= move;
				divsqure[i][1] += move*2;
				divsqure[i][2] -= move*2;
				divsqure[i][3] += move;
			}
			break;
		case 3:
			if (divsqure[i][0] >= divsqure[i][2]) {
				divsqure[i][0] = -10;
				divsqure[i][1] = -10;
				divsqure[i][2] = -10;
				divsqure[i][3] = -10;
			}
			else{
				divsqure[i][0] += move*2;
				divsqure[i][1] += move*2;
				divsqure[i][2] += move;
				divsqure[i][3] += move;
			}
			break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}