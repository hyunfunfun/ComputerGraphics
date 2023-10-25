#include "Header.h"

GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Movesqure(int x, int y);
void Mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);

int squrecount = 1;
bool button_down = false;
float prevx;
float prevy;
float COx = 0.0f;
float COy = 0.0f;
float rectsize = 0.1f;
float squre1[4] = { COx-rectsize, COy-rectsize, COx+rectsize, COy+rectsize };
float squre2[4];
float squre3[4];
float squre4[4];
float squre5[5];


void main(int argc, char **argv) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Example3");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unalbe to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Movesqure);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1f, 0.5f, 0.5f);
	glRectf(squre1[0], squre1[1], squre1[2], squre1[3]);

	glColor3f(0.5f, 0.3f, 0.3f);
	glRectf(squre2[0], squre2[1], squre2[2], squre2[3]);

	glColor3f(0.8f, 0.1f, 0.1f);
	glRectf(squre3[0], squre3[1], squre3[2], squre3[3]);

	glColor3f(0.5f, 1.0f, 0.6f);
	glRectf(squre4[0], squre4[1], squre4[2], squre4[3]);

	glColor3f(0.5f, 0.1f, 0.8f);
	glRectf(squre5[0], squre5[1], squre5[2], squre5[3]);
	glutSwapBuffers();
}
void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		squrecount++;
		float ranx = (((rand() % 19)+1) / 10.0)-1;
		float rany = (((rand() % 19)+1) / 10.0)-1;
		switch (squrecount) {
		case 2:
			squre2[0] = ranx - rectsize;
			squre2[1] = rany - rectsize;
			squre2[2] = ranx + rectsize;
			squre2[3] = rany + rectsize;
			glutDisplayFunc(drawScene);
			glutPostRedisplay();
			break;
		case 3:
			squre3[0] = ranx - rectsize;
			squre3[1] = rany - rectsize;
			squre3[2] = ranx + rectsize;
			squre3[3] = rany + rectsize;
			glutDisplayFunc(drawScene);
			glutPostRedisplay();
			break;
		case 4:
			squre4[0] = ranx - rectsize;
			squre4[1] = rany - rectsize;
			squre4[2] = ranx + rectsize;
			squre4[3] = rany + rectsize;
			glutDisplayFunc(drawScene);
			glutPostRedisplay();
			break;
		case 5:
			squre5[0] = ranx - rectsize;
			squre5[1] = rany - rectsize;
			squre5[2] = ranx + rectsize;
			squre5[3] = rany + rectsize;
			glutDisplayFunc(drawScene);
			glutPostRedisplay();
			break;
		}


		break;
	}
}


void Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN&& ogx > squre1[0] && ogx <squre1[2] && ogy >squre1[1] && ogy < squre1[3]) {
		prevx = ogx;
		prevy = ogy;
		button_down = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre2[0] && ogx <squre2[2] && ogy >squre2[1] && ogy < squre2[3]) {
		prevx = ogx;
		prevy = ogy;
		button_down = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre3[0] && ogx <squre3[2] && ogy >squre3[1] && ogy < squre3[3]) {
		prevx = ogx;
		prevy = ogy;
		button_down = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre4[0] && ogx <squre4[2] && ogy >squre4[1] && ogy < squre4[3]) {
		prevx = ogx;
		prevy = ogy;
		button_down = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ogx > squre5[0] && ogx <squre5[2] && ogy >squre5[1] && ogy < squre5[3]) {
		prevx = ogx;
		prevy = ogy;
		button_down = true;
	}
	else {
		button_down = false;
	}

}
void Movesqure(int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	if (button_down == true && ogx > squre1[0] && ogx <squre1[2] && ogy >squre1[1] && ogy < squre1[3]) {
		
		squre1[0] += (ogx - prevx);
		squre1[1] += (ogy - prevy);
		squre1[2] += (ogx - prevx);
		squre1[3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;
		glutPostRedisplay();
	}
	else if (button_down == true && ogx > squre2[0] && ogx <squre2[2] && ogy >squre2[1] && ogy < squre2[3]) {
		squre2[0] += (ogx - prevx);
		squre2[1] += (ogy - prevy);
		squre2[2] += (ogx - prevx);
		squre2[3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;
		glutPostRedisplay();
	}
	else if (button_down == true && ogx > squre2[0] && ogx <squre2[2] && ogy >squre2[1] && ogy < squre2[3]) {
		squre3[0] += (ogx - prevx);
		squre3[1] += (ogy - prevy);
		squre3[2] += (ogx - prevx);
		squre3[3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;
		glutPostRedisplay();
	}
	else if (button_down == true && ogx > squre3[0] && ogx <squre3[2] && ogy >squre3[1] && ogy < squre3[3]) {
		squre3[0] += (ogx - prevx);
		squre3[1] += (ogy - prevy);
		squre3[2] += (ogx - prevx);
		squre3[3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;
		glutPostRedisplay();
	}
	else if (button_down == true && ogx > squre4[0] && ogx <squre4[2] && ogy >squre4[1] && ogy < squre4[3]) {
		squre4[0] += (ogx - prevx);
		squre4[1] += (ogy - prevy);
		squre4[2] += (ogx - prevx);
		squre4[3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;
		glutPostRedisplay();
	}
	else if (button_down == true && ogx > squre5[0] && ogx <squre5[2] && ogy >squre5[1] && ogy < squre5[3]) {
		squre5[0] += (ogx - prevx);
		squre5[1] += (ogy - prevy);
		squre5[2] += (ogx - prevx);
		squre5[3] += (ogy - prevy);
		prevx = ogx;
		prevy = ogy;
		glutPostRedisplay();
	}

}
