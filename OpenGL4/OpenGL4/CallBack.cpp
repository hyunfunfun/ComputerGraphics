#include "CallBack.h"
#include "Header.h"

int squrecount = 1;
float squresize = 0.05f;

bool atimer = true;
bool itimer = true;
bool ctimer = true;
bool otimer = true;

bool astop = true;
bool istop = true;
bool cstop = true;
bool ostop = true;

float squre1[8] = {0,0,0,0,0,0,0,1.0};
float squre2[8] = { 0,0,0,0,0,0,0,1.0 };
float squre3[8] = { 0,0,0,0,0,0,0,1.0 };
float squre4[8] = { 0,0,0,0,0,0,0,1.0 };
float squre5[8] = { 0,0,0,0,0,0,0,1.0 };


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

GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		if (astop==true) {
			glutTimerFunc(3, aTimer, 1);
			astop = false;
		}
		else {
			astop = true;
			atimer = !atimer;
		}
		break;
	case 'i':
		break;
	case 'c':
		break;
	case 'o':
		break;
	case 's':
		break;
	case 'm':
		break;
	case 'r':
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}

GLvoid aTimer(int value) {
	float move = 0.001;
	if (atimer == true) {
		//squre1 move
		if (squre1[7] == 1.0) {
			if (squre1[2] >= 1) {
				squre1[7] = 2.0;
			}
			else if (squre1[3] >= 1) {
				squre1[7] = 4.0;
			}
			else {
				squre1[0] += move;
				squre1[1] += move;
				squre1[2] += move;
				squre1[3] += move;
			}
		}
		if (squre1[7] == 2.0) {
			if (squre1[3] >= 1) {
				squre1[7] = 3.0;
			}
			else if (squre1[0] <= -1) {
				squre1[7] = 1.0;
			}
			else {
				squre1[0] -= move;
				squre1[1] += move;
				squre1[2] -= move;
				squre1[3] += move;
			}
		}
		if (squre1[7] == 3.0) {
			if (squre1[0] <= -1) {
				squre1[7] = 4.0;
			}
			else if (squre1[1] <= -1) {
				squre1[7] = 2.0;
			}
			else {
				squre1[0] -= move;
				squre1[1] -= move;
				squre1[2] -= move;
				squre1[3] -= move;
			}
		}
		if (squre1[7] == 4.0) {
			if (squre1[1] <= -1) {
				squre1[7] = 1.0;
			}
			else if (squre1[2] >= 1) {
				squre1[7] = 3.0;
			}
			else {
				squre1[0] += move;
				squre1[1] -= move;
				squre1[2] += move;
				squre1[3] -= move;
			}
		}
		//squre2 move
		if (squre2[7] == 1.0) {
			if (squre2[2] >= 1) {
				squre2[7] = 2.0;
			}
			else if (squre2[3] >= 1) {
				squre2[7] = 4.0;
			}
			else {
				squre2[0] += move;
				squre2[1] += move;
				squre2[2] += move;
				squre2[3] += move;
			}
		}
		if (squre2[7] == 2.0) {
			if (squre2[3] >= 1) {
				squre2[7] = 3.0;
			}
			else if (squre2[0] <= -1) {
				squre2[7] = 1.0;
			}
			else {
				squre2[0] -= move;
				squre2[1] += move;
				squre2[2] -= move;
				squre2[3] += move;
			}
		}
		if (squre2[7] == 3.0) {
			if (squre2[0] <= -1) {
				squre2[7] = 4.0;
			}
			else if (squre2[1] <= -1) {
				squre2[7] = 2.0;
			}
			else {
				squre2[0] -= move;
				squre2[1] -= move;
				squre2[2] -= move;
				squre2[3] -= move;
			}
		}
		if (squre2[7] == 4.0) {
			if (squre2[1] <= -1) {
				squre2[7] = 1.0;
			}
			else if (squre2[2] >= 1) {
				squre2[7] = 3.0;
			}
			else {
				squre2[0] += move;
				squre2[1] -= move;
				squre2[2] += move;
				squre2[3] -= move;
			}
		}
		//squre3 move
		if (squre3[7] == 1.0) {
			if (squre3[2] >= 1) {
				squre3[7] = 2.0;
			}
			else if (squre3[3] >= 1) {
				squre1[7] = 4.0;
			}
			else {
				squre3[0] += move;
				squre3[1] += move;
				squre3[2] += move;
				squre3[3] += move;
			}
		}
		if (squre3[7] == 2.0) {
			if (squre3[3] >= 1) {
				squre3[7] = 3.0;
			}
			else if (squre3[0] <= -1) {
				squre3[7] = 1.0;
			}
			else {
				squre3[0] -= move;
				squre3[1] += move;
				squre3[2] -= move;
				squre3[3] += move;
			}
		}
		if (squre3[7] == 3.0) {
			if (squre3[0] <= -1) {
				squre3[7] = 4.0;
			}
			else if (squre3[1] <= -1) {
				squre3[7] = 2.0;
			}
			else {
				squre3[0] -= move;
				squre3[1] -= move;
				squre3[2] -= move;
				squre3[3] -= move;
			}
		}
		if (squre3[7] == 4.0) {
			if (squre3[1] <= -1) {
				squre3[7] = 1.0;
			}
			else if (squre3[2] >= 1) {
				squre3[7] = 3.0;
			}
			else {
				squre3[0] += move;
				squre3[1] -= move;
				squre3[2] += move;
				squre3[3] -= move;
			}
		}
		//squre4 move
		if (squre4[7] == 1.0) {
			if (squre4[2] >= 1) {
				squre4[7] = 2.0;
			}
			else if (squre4[3] >= 1) {
				squre4[7] = 4.0;
			}
			else {
				squre4[0] += move;
				squre4[1] += move;
				squre4[2] += move;
				squre4[3] += move;
			}
		}
		if (squre4[7] == 2.0) {
			if (squre4[3] >= 1) {
				squre4[7] = 3.0;
			}
			else if (squre4[0] <= -1) {
				squre4[7] = 1.0;
			}
			else {
				squre4[0] -= move;
				squre4[1] += move;
				squre4[2] -= move;
				squre4[3] += move;
			}
		}
		if (squre4[7] == 3.0) {
			if (squre4[0] <= -1) {
				squre4[7] = 4.0;
			}
			else if (squre4[1] <= -1) {
				squre4[7] = 2.0;
			}
			else {
				squre4[0] -= move;
				squre4[1] -= move;
				squre4[2] -= move;
				squre4[3] -= move;
			}
		}
		if (squre4[7] == 4.0) {
			if (squre4[1] <= -1) {
				squre4[7] = 1.0;
			}
			else if (squre4[2] >= 1) {
				squre4[7] = 3.0;
			}
			else {
				squre4[0] += move;
				squre4[1] -= move;
				squre4[2] += move;
				squre4[3] -= move;
			}
		}
		//squre5 move
		if (squre5[7] == 1.0) {
			if (squre5[2] >= 1) {
				squre5[7] = 2.0;
			}
			else if (squre5[3] >= 1) {
				squre5[7] = 4.0;
			}
			else {
				squre5[0] += move;
				squre5[1] += move;
				squre5[2] += move;
				squre5[3] += move;
			}
		}
		if (squre5[7] == 2.0) {
			if (squre5[3] >= 1) {
				squre5[7] = 3.0;
			}
			else if (squre5[0] <= -1) {
				squre5[7] = 1.0;
			}
			else {
				squre5[0] -= move;
				squre5[1] += move;
				squre5[2] -= move;
				squre5[3] += move;
			}
		}
		if (squre5[7] == 3.0) {
			if (squre5[0] <= -1) {
				squre5[7] = 4.0;
			}
			else if (squre5[1] <= -1) {
				squre5[7] = 2.0;
			}
			else {
				squre5[0] -= move;
				squre5[1] -= move;
				squre5[2] -= move;
				squre5[3] -= move;
			}
		}
		if (squre5[7] == 4.0) {
			if (squre5[1] <= -1) {
				squre5[7] = 1.0;
			}
			else if (squre5[2] >= 1) {
				squre5[7] = 3.0;
			}
			else {
				squre5[0] += move;
				squre5[1] -= move;
				squre5[2] += move;
				squre5[3] -= move;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(3, aTimer, 1);
	}

}
GLvoid iTimer(int value) {

}
GLvoid cTimer(int value) {

}
GLvoid oTimer(int value) {

}