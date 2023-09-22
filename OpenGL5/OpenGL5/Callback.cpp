#include "Header.h"
#include "Callback.h"

float squre[21][7];
float rectsize = 0.05;
float prevx;
float prevy;
bool button_down = false;

int click;

GLvoid defsqure() {
	for (int i = 0; i < 20; i++) {
		float ranx = (((rand() % 19) + 1) / 10.0) - 1;
		float rany = (((rand() % 19) + 1) / 10.0) - 1;
		squre[i][0] = ranx - rectsize;
		squre[i][1] = rany - rectsize;
		squre[i][2] = ranx + rectsize;
		squre[i][3] = rany + rectsize;
		for (int j = 4; j < 7; j++) {
			squre[i][j] = ((rand() % 10) + 1) / 10.0;
		}
	}
}
GLvoid drawScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 21; i++) {
		glColor3f(squre[i][4], squre[i][5], squre[i][6]);
		glRectf(squre[i][0], squre[i][1], squre[i][2], squre[i][3]);
	}
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
		//지우개 사각형 생성
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){	
			squre[20][0] = ogx - (rectsize*2);
			squre[20][1] = ogy - (rectsize * 2);
			squre[20][2] = ogx + (rectsize * 2);
			squre[20][3] = ogy + (rectsize * 2);
			squre[20][4] = 0.0f;
			squre[20][5] = 0.0f;
			squre[20][6] = 0.0f;

			prevx = ogx;
			prevy = ogy;
			button_down = true;
		}
		//클릭버튼을 뗄 경우 사각형 삭제
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP ){
			squre[20][0] = NULL;
			squre[20][1] = NULL;
			squre[20][2] = NULL;
			squre[20][3] = NULL;
			button_down = false;
	}
}
GLvoid Motion(int x, int y) {
	float sizeup = 0.01;
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	//지우개 사각형 움직이기
	if (button_down == true) {
		squre[20][0] += (ogx - prevx);
		squre[20][1] += (ogy - prevy);
		squre[20][2] += (ogx - prevx);
		squre[20][3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;

		//지우개 사각형과 닿은 사각형지우고, 지우개 사각형 크기증가
		for (int i = 0; i < 20; i++) {
			if ( (squre[i][0] <= squre[20][2]) && (squre[i][1] <= squre[20][3]) && (squre[i][2] >= squre[20][0]) && (squre[i][3] >= squre[20][1])) {
				squre[i][0] = -10;
				squre[i][1] = -10;
				squre[i][2] = -10;
				squre[i][3] = -10;
				squre[20][4] = squre[i][4];
				squre[20][5] = squre[i][5];
				squre[20][6] = squre[i][6];
				squre[20][0] -= sizeup;
				squre[20][1] -= sizeup;
				squre[20][2] += sizeup;
				squre[20][3] += sizeup;
			}
		}
		glutPostRedisplay();
	}
}

GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		defsqure();
		glutPostRedisplay();
		break;
	}
}