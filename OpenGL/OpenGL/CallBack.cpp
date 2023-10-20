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

float squre1[8];
float squre2[8];
float squre3[8];
float squre4[8];
float squre5[8];


bool squre1c = true;
bool squre2c = true;
bool squre3c = true;
bool squre4c = true;
bool squre5c = true;

bool squre1size = true;
bool squre2size = true;
bool squre3size = true;
bool squre4size = true;
bool squre5size = true;

float prevsqure1[4];
float prevsqure2[4];
float prevsqure3[4];
float prevsqure4[4];
float prevsqure5[4];


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
			prevsqure1[0] = squre1[0];
			prevsqure1[1] = squre1[1];
			prevsqure1[2] = squre1[2];
			prevsqure1[3] = squre1[3];

			squre1[4] = (rand() % 10 / 10.0);
			squre1[5] = (rand() % 10 / 10.0);
			squre1[6] = (rand() % 10 / 10.0);
			break;
		case 2:
			squre2[0] = ogx - squresize;
			squre2[1] = ogy - squresize;
			squre2[2] = ogx + squresize;
			squre2[3] = ogy + squresize;
			prevsqure2[0] = squre2[0];
			prevsqure2[1] = squre2[1];
			prevsqure2[2] = squre2[2];
			prevsqure2[3] = squre2[3];

			squre2[4] = (rand() % 10 / 10.0);
			squre2[5] = (rand() % 10 / 10.0);
			squre2[6] = (rand() % 10 / 10.0);
			break;
		case 3:
			squre3[0] = ogx - squresize;
			squre3[1] = ogy - squresize;
			squre3[2] = ogx + squresize;
			squre3[3] = ogy + squresize;
			prevsqure3[0] = squre3[0];
			prevsqure3[1] = squre3[1];
			prevsqure3[2] = squre3[2];
			prevsqure3[3] = squre3[3];

			squre3[4] = (rand() % 10 / 10.0);
			squre3[5] = (rand() % 10 / 10.0);
			squre3[6] = (rand() % 10 / 10.0);
			break;
		case 4:
			squre4[0] = ogx - squresize;
			squre4[1] = ogy - squresize;
			squre4[2] = ogx + squresize;
			squre4[3] = ogy + squresize;
			prevsqure4[0] = squre4[0];
			prevsqure4[1] = squre4[1];
			prevsqure4[2] = squre4[2];
			prevsqure4[3] = squre4[3];
			squre4[4] = (rand() % 10 / 10.0);
			squre4[5] = (rand() % 10 / 10.0);
			squre4[6] = (rand() % 10 / 10.0);
			break;
		case 5:
			squre5[0] = ogx - squresize;
			squre5[1] = ogy - squresize;
			squre5[2] = ogx + squresize;
			squre5[3] = ogy + squresize;
			prevsqure5[0] = squre5[0];
			prevsqure5[1] = squre5[1];
			prevsqure5[2] = squre5[2];
			prevsqure5[3] = squre5[3];

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
		squre1[7] = 1.0;
		squre2[7] = 1.0;
		squre3[7] = 1.0;
		squre4[7] = 1.0;
		squre5[7] = 1.0;
		if (astop==true) {
			glutTimerFunc(3, aTimer, 1);
			itimer = !itimer;
			astop = false;
		}
		else {
			astop = true;
			atimer = !atimer;
		}
		break;
	case 'i':
		squre1[7] = squre1[1];
		squre2[7] = squre2[1];
		squre3[7] = squre3[1];
		squre4[7] = squre4[1];
		squre5[7] = squre5[1];
		if (istop == true) {
			glutTimerFunc(3, iTimer, 1);
			atimer = !atimer;
			istop = false;
		}
		else {
			istop = true;
			itimer = !itimer;
		}
		break;
	case 'c':
		if (cstop == true) {
			glutTimerFunc(3, cTimer, 1);
			cstop = false;
		}
		else {
			cstop = true;
			ctimer = !ctimer;
		}
		break;
	case 'o':
		if (ostop == true) {
			glutTimerFunc(50, oTimer, 1);
			ostop = false;
		}
		else {
			ostop = true;
			otimer = !otimer;
		}
		break;
	case 's':
		astop = true;
		atimer = !atimer;
		istop = true;
		itimer = !itimer;
		cstop = true;
		ctimer = !ctimer;
		ostop = true;
		otimer = !otimer;
		break;
	case 'm':
		for (int i = 0; i < 4; i++) {
			squre1[i] = prevsqure1[i];
			squre2[i] = prevsqure2[i];
			squre3[i] = prevsqure3[i];
			squre4[i] = prevsqure4[i];
			squre5[i] = prevsqure5[i];
			glutPostRedisplay();
		}
		break;
	case 'r':
		squrecount = 1;
		for (int i = 0; i < 8; i++) {
			squre1[i] = NULL;
			squre2[i] = NULL;
			squre3[i] = NULL;
			squre4[i] = NULL;
			squre5[i] = NULL;
		}
		glutPostRedisplay();
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
	float move = 0.001;
	
	if (itimer == true) {
		//squre1 move
		if (squre1c==true) {
			if (squre1[1] >= squre1[7] + 0.1) {
				squre1c = false;
			}
			else {
				if (squre1[2] > 1) {
					squre1[2] = (squre1[2] - squre1[0])-1;
					squre1[0] = -1;
				}
				squre1[0] += move;
				squre1[1] += move;
				squre1[2] += move;
				squre1[3] += move;
			}
		}
		else if (squre1c==false) {
			if (squre1[1] <= squre1[7] - 0.1) {
				squre1c = true;
			}
			else {
				if (squre1[2] > 1) {
					squre1[2] = (squre1[2] - squre1[0]) - 1;
					squre1[0] = -1;
				}
				squre1[0] += move;
				squre1[1] -= move;
				squre1[2] += move;
				squre1[3] -= move;
			}
		}
		//squre2 move
		if (squre2c == true) {
			if (squre2[1] >= squre2[7] + 0.1) {
				squre2c = false;
			}
			else {
				if (squre2[2] > 1) {
					squre2[2] = (squre2[2] - squre2[0]) - 1;
					squre2[0] = -1;
				}
				squre2[0] += move;
				squre2[1] += move;
				squre2[2] += move;
				squre2[3] += move;
			}
		}
		else if (squre2c == false) {
			if (squre2[1] <= squre2[7] - 0.1) {
				squre2c = true;
			}
			else {
				if (squre2[2] > 1) {
					squre2[2] = (squre2[2] - squre2[0]) - 1;
					squre2[0] = -1;
				}
				squre2[0] += move;
				squre2[1] -= move;
				squre2[2] += move;
				squre2[3] -= move;
			}
		}
		//squre3 move
		if (squre3c == true) {
			if (squre3[1] >= squre3[7] + 0.1) {
				squre3c = false;
			}
			else {
				if (squre3[2] > 1) {
					squre3[2] = (squre3[2] - squre3[0]) - 1;
					squre3[0] = -1;
				}
				squre3[0] += move;
				squre3[1] += move;
				squre3[2] += move;
				squre3[3] += move;
			}
		}
		else if (squre3c == false) {
			if (squre3[1] <= squre3[7] - 0.1) {
				squre3c = true;
			}
			else {
				if (squre3[2] > 1) {
					squre3[2] = (squre3[2] - squre3[0]) - 1;
					squre3[0] = -1;
				}
				squre3[0] += move;
				squre3[1] -= move;
				squre3[2] += move;
				squre3[3] -= move;
			}
		}
		//squre4 move
		if (squre4c == true) {
			if (squre4[1] >= squre4[7] + 0.1) {
				squre4c = false;
			}
			else {
				if (squre4[2] > 1) {
					squre4[2] = (squre4[2] - squre4[0]) - 1;
					squre4[0] = -1;
				}
				squre4[0] += move;
				squre4[1] += move;
				squre4[2] += move;
				squre4[3] += move;
			}
		}
		else if (squre4c == false) {
			if (squre4[1] <= squre4[7] - 0.1) {
				squre4c = true;
			}
			else {
				if (squre4[2] > 1) {
					squre4[2] = (squre4[2] - squre4[0]) - 1;
					squre4[0] = -1;
				}
				squre4[0] += move;
				squre4[1] -= move;
				squre4[2] += move;
				squre4[3] -= move;
			}
		}
		//squre5 move
		if (squre5c == true) {
			if (squre5[1] >= squre5[7] + 0.1) {
				squre5c = false;
			}
			else {
				if (squre5[2] > 1) {
					squre5[2] = (squre5[2] - squre5[0]) - 1;
					squre5[0] = -1;
				}
				squre5[0] += move;
				squre5[1] += move;
				squre5[2] += move;
				squre5[3] += move;
			}
		}
		else if (squre5c == false) {
			if (squre5[1] <= squre5[7] - 0.1) {
				squre5c = true;
			}
			else {
				if (squre5[2] > 1) {
					squre5[2] = (squre5[2] - squre5[0]) - 1;
					squre5[0] = -1;
				}
				squre5[0] += move;
				squre5[1] -= move;
				squre5[2] += move;
				squre5[3] -= move;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(3, iTimer, 1);
	}

}

GLvoid cTimer(int value) {
	float sizeup = 0.0001;
	if (ctimer == true) {
		//squre1 size
		if (squre1size==true) {
			if (squre1[0] - squre1[2] > 0.3) {
				squre1size = false;
			}
			else {
				squre1[0] += sizeup;
				squre1[1] += sizeup;
				squre1[2] -= sizeup;
				squre1[3] -= sizeup;
			}
		}
		else if(squre1size==false){
			if (squre1[0] - squre1[2] < 0.05) {
				squre1size = true;
			}
			else {
				squre1[0] -= sizeup;
				squre1[1] -= sizeup;
				squre1[2] += sizeup;
				squre1[3] += sizeup;
			}
		}
		//squre2 size
		if (squre2size == true) {
			if (squre2[0] - squre2[2] > 0.3) {
				squre2size = false;
			}
			else {
				squre2[0] += sizeup;
				squre2[1] += sizeup;
				squre2[2] -= sizeup;
				squre2[3] -= sizeup;
			}
		}
		else if (squre2size == false) {
			if (squre2[0] - squre2[2] < 0.05) {
				squre2size = true;
			}
			else {
				squre2[0] -= sizeup;
				squre2[1] -= sizeup;
				squre2[2] += sizeup;
				squre2[3] += sizeup;
			}
		}
		//squre3 size
		if (squre3size == true) {
			if (squre3[0] - squre3[2] > 0.3) {
				squre3size = false;
			}
			else {
				squre3[0] += sizeup;
				squre3[1] += sizeup;
				squre3[2] -= sizeup;
				squre3[3] -= sizeup;
			}
		}
		else if (squre3size == false) {
			if (squre3[0] - squre3[2] < 0.05) {
				squre3size = true;
			}
			else {
				squre3[0] -= sizeup;
				squre3[1] -= sizeup;
				squre3[2] += sizeup;
				squre3[3] += sizeup;
			}
		}
		//squre4 size
		if (squre4size == true) {
			if (squre4[0] - squre4[2] > 0.3) {
				squre4size = false;
			}
			else {
				squre4[0] += sizeup;
				squre4[1] += sizeup;
				squre4[2] -= sizeup;
				squre4[3] -= sizeup;
			}
		}
		else if (squre4size == false) {
			if (squre4[0] - squre4[2] < 0.05) {
				squre4size = true;
			}
			else {
				squre4[0] -= sizeup;
				squre4[1] -= sizeup;
				squre4[2] += sizeup;
				squre4[3] += sizeup;
			}
		}
		//squre5 size
		if (squre5size == true) {
			if (squre5[0] - squre5[2] > 0.3) {
				squre5size = false;
			}
			else {
				squre5[0] += sizeup;
				squre5[1] += sizeup;
				squre5[2] -= sizeup;
				squre5[3] -= sizeup;
			}
		}
		else if (squre5size == false) {
			if (squre5[0] - squre5[2] < 0.05) {
				squre5size = true;
			}
			else {
				squre5[0] -= sizeup;
				squre5[1] -= sizeup;
				squre5[2] += sizeup;
				squre5[3] += sizeup;
			}
		}
		glutPostRedisplay();
		glutTimerFunc(3, cTimer, 1);
	}
}

GLvoid oTimer(int value) {
	if (ctimer == true) {
		squre1[4] = (rand() % 10 / 10.0);
		squre1[5] = (rand() % 10 / 10.0);
		squre1[6] = (rand() % 10 / 10.0);

		squre2[4] = (rand() % 10 / 10.0);
		squre2[5] = (rand() % 10 / 10.0);
		squre2[6] = (rand() % 10 / 10.0);

		squre3[4] = (rand() % 10 / 10.0);
		squre3[5] = (rand() % 10 / 10.0);
		squre3[6] = (rand() % 10 / 10.0);

		squre4[4] = (rand() % 10 / 10.0);
		squre4[5] = (rand() % 10 / 10.0);
		squre4[6] = (rand() % 10 / 10.0);

		squre5[4] = (rand() % 10 / 10.0);
		squre5[5] = (rand() % 10 / 10.0);
		squre5[6] = (rand() % 10 / 10.0);

		glutPostRedisplay();
		glutTimerFunc(50, oTimer, 1);
	}
}