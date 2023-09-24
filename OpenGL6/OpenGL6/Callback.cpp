#include "Header.h"
#include "CallBack.h"

float squre[5][7];
float divsqure1[4][7];
float divsqure2[4][7];
float divsqure3[4][7];
float divsqure4[4][7];
float divsqure5[8][7];
float rectsize = 0.1;
int squreindx;

bool sqr1stop = false;
bool sqr2stop = false;
bool sqr3stop = false;
bool sqr4stop = false;
bool sqr5stop = false;

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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			divsqure1[i][j] = -10;
			divsqure2[i][j] = -10;
			divsqure3[i][j] = -10;
			divsqure4[i][j] = -10;
			divsqure5[i][j] = -10;
			divsqure5[i+4][j] = -10;
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
	for (int i = 0; i < 4; i++) {
		glColor3f(divsqure3[i][4], divsqure3[i][5], divsqure3[i][6]);
		glRectf(divsqure3[i][0], divsqure3[i][1], divsqure3[i][2], divsqure3[i][3]);
	}
	for (int i = 0; i < 4; i++) {
		glColor3f(divsqure4[i][4], divsqure4[i][5], divsqure4[i][6]);
		glRectf(divsqure4[i][0], divsqure4[i][1], divsqure4[i][2], divsqure4[i][3]);
	}
	for (int i = 0; i < 8; i++) {
		glColor3f(divsqure5[i][4], divsqure5[i][5], divsqure5[i][6]);
		glRectf(divsqure5[i][0], divsqure5[i][1], divsqure5[i][2], divsqure5[i][3]);
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 
		ogx > squre[0][0] && ogx <squre[0][2] && ogy >squre[0][1] && ogy < squre[0][3]) {
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && 
		ogx > squre[1][0] && ogx <squre[1][2] && ogy >squre[1][1] && ogy < squre[1][3]) {
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
	//squre2 ³ª´©±â
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		ogx > squre[2][0] && ogx <squre[2][2] && ogy >squre[2][1] && ogy < squre[2][3]) {
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				divsqure3[i][0] = squre[2][0];
				divsqure3[i][1] = squre[2][1];
				divsqure3[i][2] = squre[2][2] - rectsize;
				divsqure3[i][3] = squre[2][3] - rectsize;
				divsqure3[i][4] = squre[2][4];
				divsqure3[i][5] = squre[2][5];
				divsqure3[i][6] = squre[2][6];
				break;
			case 1:
				divsqure3[i][0] = squre[2][0] + rectsize;
				divsqure3[i][1] = squre[2][1];
				divsqure3[i][2] = squre[2][2];
				divsqure3[i][3] = squre[2][3] - rectsize;
				divsqure3[i][4] = squre[2][4];
				divsqure3[i][5] = squre[2][5];
				divsqure3[i][6] = squre[2][6];
				break;
			case 2:
				divsqure3[i][0] = squre[2][0];
				divsqure3[i][1] = squre[2][1] + rectsize;
				divsqure3[i][2] = squre[2][2] - rectsize;
				divsqure3[i][3] = squre[2][3];
				divsqure3[i][4] = squre[2][4];
				divsqure3[i][5] = squre[2][5];
				divsqure3[i][6] = squre[2][6];
				break;
			case 3:
				divsqure3[i][0] = squre[2][0] + rectsize;
				divsqure3[i][1] = squre[2][1] + rectsize;
				divsqure3[i][2] = squre[2][2];
				divsqure3[i][3] = squre[2][3];
				divsqure3[i][4] = squre[2][4];
				divsqure3[i][5] = squre[2][5];
				divsqure3[i][6] = squre[2][6];
				break;
			}
		}
		squre[2][0] = -12;
		squre[2][1] = -12;
		squre[2][2] = -12;
		squre[2][3] = -12;
		sqr3stop = true;
		glutTimerFunc(10, Timer3, 0);
	}
	//squre3 ³ª´©±â
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		ogx > squre[3][0] && ogx <squre[3][2] && ogy >squre[3][1] && ogy < squre[3][3]) {
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				divsqure4[i][0] = squre[3][0];
				divsqure4[i][1] = squre[3][1];
				divsqure4[i][2] = squre[3][2] - rectsize;
				divsqure4[i][3] = squre[3][3] - rectsize;
				divsqure4[i][4] = squre[3][4];
				divsqure4[i][5] = squre[3][5];
				divsqure4[i][6] = squre[3][6];
				break;
			case 1:
				divsqure4[i][0] = squre[3][0] + rectsize;
				divsqure4[i][1] = squre[3][1];
				divsqure4[i][2] = squre[3][2];
				divsqure4[i][3] = squre[3][3] - rectsize;
				divsqure4[i][4] = squre[3][4];
				divsqure4[i][5] = squre[3][5];
				divsqure4[i][6] = squre[3][6];
				break;
			case 2:
				divsqure4[i][0] = squre[3][0];
				divsqure4[i][1] = squre[3][1] + rectsize;
				divsqure4[i][2] = squre[3][2] - rectsize;
				divsqure4[i][3] = squre[3][3];
				divsqure4[i][4] = squre[3][4];
				divsqure4[i][5] = squre[3][5];
				divsqure4[i][6] = squre[3][6];
				break;
			case 3:
				divsqure4[i][0] = squre[3][0] + rectsize;
				divsqure4[i][1] = squre[3][1] + rectsize;
				divsqure4[i][2] = squre[3][2];
				divsqure4[i][3] = squre[3][3];
				divsqure4[i][4] = squre[3][4];
				divsqure4[i][5] = squre[3][5];
				divsqure4[i][6] = squre[3][6];
				break;
			}
		}
		squre[3][0] = -12;
		squre[3][1] = -12;
		squre[3][2] = -12;
		squre[3][3] = -12;
		sqr4stop = true;
		glutTimerFunc(10, Timer4, 0);
	}
	//squre4 ³ª´©±â
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		ogx > squre[4][0] && ogx <squre[4][2] && ogy >squre[4][1] && ogy < squre[4][3]) {
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				divsqure5[i][0] = squre[4][0];
				divsqure5[i][1] = squre[4][1];
				divsqure5[i][2] = squre[4][2] - rectsize;
				divsqure5[i][3] = squre[4][3] - rectsize;
				divsqure5[i][4] = squre[4][4];
				divsqure5[i][5] = squre[4][5];
				divsqure5[i][6] = squre[4][6];

				divsqure5[i+4][0] = squre[4][0];
				divsqure5[i+4][1] = squre[4][1];
				divsqure5[i+4][2] = squre[4][2] - rectsize;
				divsqure5[i+4][3] = squre[4][3] - rectsize;
				divsqure5[i+4][4] = squre[4][4];
				divsqure5[i+4][5] = squre[4][5];
				divsqure5[i+4][6] = squre[4][6];
				break;
			case 1:
				divsqure5[i][0] = squre[4][0] + rectsize;
				divsqure5[i][1] = squre[4][1];
				divsqure5[i][2] = squre[4][2];
				divsqure5[i][3] = squre[4][3] - rectsize;
				divsqure5[i][4] = squre[4][4];
				divsqure5[i][5] = squre[4][5];
				divsqure5[i][6] = squre[4][6];

				divsqure5[i+4][0] = squre[4][0] + rectsize;
				divsqure5[i+4][1] = squre[4][1];
				divsqure5[i+4][2] = squre[4][2];
				divsqure5[i+4][3] = squre[4][3] - rectsize;
				divsqure5[i+4][4] = squre[4][4];
				divsqure5[i+4][5] = squre[4][5];
				divsqure5[i+4][6] = squre[4][6];
				break;
			case 2:
				divsqure5[i][0] = squre[4][0];
				divsqure5[i][1] = squre[4][1] + rectsize;
				divsqure5[i][2] = squre[4][2] - rectsize;
				divsqure5[i][3] = squre[4][3];
				divsqure5[i][4] = squre[4][4];
				divsqure5[i][5] = squre[4][5];
				divsqure5[i][6] = squre[4][6];

				divsqure5[i+4][0] = squre[4][0];
				divsqure5[i+4][1] = squre[4][1] + rectsize;
				divsqure5[i+4][2] = squre[4][2] - rectsize;
				divsqure5[i+4][3] = squre[4][3];
				divsqure5[i+4][4] = squre[4][4];
				divsqure5[i+4][5] = squre[4][5];
				divsqure5[i+4][6] = squre[4][6];
				break;
			case 3:
				divsqure5[i][0] = squre[4][0] + rectsize;
				divsqure5[i][1] = squre[4][1] + rectsize;
				divsqure5[i][2] = squre[4][2];
				divsqure5[i][3] = squre[4][3];
				divsqure5[i][4] = squre[4][4];
				divsqure5[i][5] = squre[4][5];
				divsqure5[i][6] = squre[4][6];

				divsqure5[i+4][0] = squre[4][0] + rectsize;
				divsqure5[i+4][1] = squre[4][1] + rectsize;
				divsqure5[i+4][2] = squre[4][2];
				divsqure5[i+4][3] = squre[4][3];
				divsqure5[i+4][4] = squre[4][4];
				divsqure5[i+4][5] = squre[4][5];
				divsqure5[i+4][6] = squre[4][6];
				break;
			}
		}
		squre[4][0] = -12;
		squre[4][1] = -12;
		squre[4][2] = -12;
		squre[4][3] = -12;
		sqr5stop = true;
		glutTimerFunc(10, Timer5, 0);
	}
}
//squre0 ¼Ò¸ê
GLvoid Timer(int value) {
	float move = 0.0005;
	if (sqr1stop==true) {
		for (int i = 0; i < 4; i++) {
			if (divsqure1[i][0] >= divsqure1[i][2]) {
				for (int j = 0; j < 4; j++) {
					divsqure1[j][0] = -10;
					divsqure1[j][1] = -10;
					divsqure1[j][2] = -10;
					divsqure1[j][3] = -10;
					sqr1stop = false;
				}
				sqr1stop = false;
				break;
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
				for (int j = 0; j < 4; j++) {
					divsqure2[j][0] = -10;
					divsqure2[j][1] = -10;
					divsqure2[j][2] = -10;
					divsqure2[j][3] = -10;
					sqr2stop = false;
				}
				sqr2stop = false;
				break;
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

//squre2 ¼Ò¸ê
GLvoid Timer3(int value) {
	float move = 0.0005;
	if (sqr3stop == true) {
		for (int i = 0; i < 4; i++) {
			if (divsqure3[i][0] >= divsqure3[i][2]) {
				for (int j = 0; j < 4; j++) {
					divsqure3[j][0] = -10;
					divsqure3[j][1] = -10;
					divsqure3[j][2] = -10;
					divsqure3[j][3] = -10;
					sqr3stop = false;
				}
				sqr3stop = false;
				break;
			}
			switch (i) {
			case 0:
				divsqure3[i][0] -= move;
				divsqure3[i][2] -= move * 2;
				break;
			case 1:
				divsqure3[i][1] -= move;
				divsqure3[i][3] -= move * 2;
				break;
			case 2:
				divsqure3[i][1] += move * 2;
				divsqure3[i][3] += move;
				break;
			case 3:
				divsqure3[i][0] += move * 2;
				divsqure3[i][2] += move;
				break;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer3, 1);
	}
}

//squre3 ¼Ò¸ê
GLvoid Timer4(int value) {
	float move = 0.0005;
	if (sqr4stop == true) {
		for (int i = 0; i < 4; i++) {
			if (divsqure4[i][0] >= divsqure4[i][2]) {
				for (int j = 0; j < 4; j++) {
					divsqure4[j][0] = -10;
					divsqure4[j][1] = -10;
					divsqure4[j][2] = -10;
					divsqure4[j][3] = -10;
					sqr4stop = false;
				}
				sqr4stop = false;
				break;
			}
			switch (i) {
			case 0:
				divsqure4[i][0] -= move;
				divsqure4[i][2] -= move * 2;
				break;
			case 1:
				divsqure4[i][1] -= move;
				divsqure4[i][3] -= move * 2;
				break;
			case 2:
				divsqure4[i][1] += move * 2;
				divsqure4[i][3] += move;
				break;
			case 3:
				divsqure4[i][0] += move * 2;
				divsqure4[i][2] += move;
				break;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer4, 1);
	}
}

//squre4 ¼Ò¸ê
GLvoid Timer5(int value) {
	float move = 0.0005;
	if (sqr5stop == true) {
		for (int i = 0; i < 4; i++) {
			if (divsqure5[i][0] >= divsqure5[i][2]) {
				for (int j = 0; j < 4; j++) {
					divsqure5[j][0] = -10;
					divsqure5[j][1] = -10;
					divsqure5[j][2] = -10;
					divsqure5[j][3] = -10;

					divsqure5[j+4][0] = -10;
					divsqure5[j+4][1] = -10;
					divsqure5[j+4][2] = -10;
					divsqure5[j+4][3] = -10;

					sqr5stop = false;
				}
				sqr5stop = false;
				break;
			}
			//if(divsqure5[i][0]-divsqure5[i][0])
			switch (i) {
			case 0:
				divsqure5[i][0] -= move;
				divsqure5[i][1] -= move;
				divsqure5[i][2] -= move*2;
				divsqure5[i][3] -= move*2;

				divsqure5[i+4][0] -= move;
				divsqure5[i + 4][1] += move;
				divsqure5[i + 4][2] -= move*2;
				
				break;
			case 1:
				divsqure5[i][1] -= move;
				divsqure5[i][2] -= move;
				divsqure5[i][3] -= move*2;
				
				divsqure5[i + 4][0] += move*2;
				divsqure5[i+4][1] -= move;
				divsqure5[i + 4][2] += move;
				divsqure5[i+4][3] -= move*2;
				break;
			case 2:
				divsqure5[i][0] -= move;
				divsqure5[i][1] += move*2;
				divsqure5[i][2] -= move*2;
				divsqure5[i][3] += move;

				divsqure5[i+4][1] += move*2;
				divsqure5[i+4][3] += move;
				divsqure5[i + 4][0] += move;
				break;
			case 3:
				divsqure5[i][0] += move*2;
				divsqure5[i][1] += move*2;
				divsqure5[i][2] += move;
				divsqure5[i][3] += move;

				divsqure5[i+4][0] += move*2;
				divsqure5[i+4][2] += move;
				divsqure5[i + 4][3] -= move;
				
				break;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer5, 1);
	}
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		defrect();
		glutPostRedisplay();
		break;
	}
}