#include "Header.h"
#include "Callback.h"

float squre[20][7];
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
	for (int i = 0; i < 20; i++) {
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
	for (int i = 0; i < 20; i++) {
		//클릭시 사각형 선택
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx>squre[i][0] && ogx <squre[i][2] && ogy >squre[i][1] && ogy < squre[i][3]) {
			prevx = ogx;
			prevy = ogy;
			button_down = true;
			click = i;
		}
		//클릭버튼을 뗄 경우 사각형 삭제
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && ogx > squre[i][0] && ogx <squre[i][2] && ogy >squre[i][1] && ogy < squre[i][3]) {
			squre[i][0] = NULL;
			squre[i][1] = NULL;
			squre[i][2] = NULL;
			squre[i][3] = NULL;
			button_down = false;
		}
	}
}
GLvoid Motion(int x, int y) {
	float sizeup = 0.01;
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	//클릭한 사각형 움직이기
	if (button_down == true) {
		squre[click][0] += (ogx - prevx);
		squre[click][1] += (ogy - prevy);
		squre[click][2] += (ogx - prevx);
		squre[click][3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;

		//클릭한 사각형과 닿은 사각형지우고, 클릭한 사각형 크기증가
		for (int i = 0; i < 20; i++) {
			if ( (squre[i][0] <= squre[click][2]) && (squre[i][1] <= squre[click][3]) && (squre[i][2] >= squre[click][0]) && (squre[i][3] >= squre[click][1])) {
				if (i == click)
					continue;
				else {
					squre[i][0] = NULL;
					squre[i][1] = NULL;
					squre[i][2] = NULL;
					squre[i][3] = NULL;
					squre[click][4] = squre[i][4];
					squre[click][5] = squre[i][5];
					squre[click][6] = squre[i][6];
					squre[click][0] -= sizeup;
					squre[click][1] -= sizeup;
					squre[click][2] += sizeup;
					squre[click][3] += sizeup;
				}
			}
		}
		glutPostRedisplay();
	}
}