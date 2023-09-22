#include "Header.h"
#include "Callback.h"

float squre[20][7];
float rectsize = 0.05;
float prevx;
float prevy;
bool button_down = false;

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
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && squre[i][0] && ogx <squre[i][2] && ogy >squre[i][1] && ogy < squre[i][3]) {
			prevx = ogx;
			prevy = ogy;
			button_down = true;
		}
	}
}
GLvoid Motion(int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	for (int i = 0; i < 20; i++) {
		if (button_down == true && ogx > squre[i][0] && ogx <squre[i][2] && ogy >squre[i][1] && ogy < squre[i][3]) {
			squre[i][0] += (ogx - prevx);
			squre[i][1] += (ogy - prevy);
			squre[i][2] += (ogx - prevx);
			squre[i][3] += (ogy - prevy);
			prevx = ogx;
			prevy = ogy;
			glutPostRedisplay();
		}
	}
}