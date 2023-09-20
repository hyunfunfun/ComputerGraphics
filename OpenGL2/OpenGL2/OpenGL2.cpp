#include "Header.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void squre();

float squre1[7] = { 1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 0.0 };
float squre2[7] = { 0.5, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0 };
float squre3[7] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, -1.0 };
float squre4[7] = { 1.0, 0.5, 0.0, -1.0, 0.0, 0.0, -1.0 };
float backcolor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	
	glutCreateWindow("Example2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unalble to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initiallized\n";
	}
	glutDisplayFunc(squre);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
void Mouse(int button, int state, int x, int y) {
	double num = 0.2;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && 
		(x > 400+squre1[3]*400 && y > 400-squre1[4]*400)&&(x<400+squre1[5]*400&&y<400-squre1[6]*400)) {
		squre1[3] = squre1[3] + num;
		squre1[4] = squre1[4] - num;
		squre1[5] = squre1[5] - num;
		squre1[6] = squre1[6] + num;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x>0&&y>0)&&(x<400&&y<400)) {
		squre1[3] = squre1[3] - num;
		squre1[4] = squre1[4] + num;
		squre1[5] = squre1[5] + num;
		squre1[6] = squre1[6] - num;
	}
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre2[3] * 400 && y > 400 - squre2[4] * 400) && (x < 400 + squre2[5] * 400 && y < 400 - squre2[6] * 400)) {
		squre2[3] = squre2[3] + num;
		squre2[4] = squre2[4] - num;
		squre2[5] = squre2[5] - num;
		squre2[6] = squre2[6] + num;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x > 400 && y > 0) && (x < 800 && y < 400)) {
		squre2[3] = squre2[3] - num;
		squre2[4] = squre2[4] + num;
		squre2[5] = squre2[5] + num;
		squre2[6] = squre2[6] - num;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre3[3] * 400 && y > 400 - squre3[4] * 400) && (x < 400 + squre3[5] * 400 && y < 400 - squre3[6] * 400)) {
		squre3[3] = squre3[3] + num;
		squre3[4] = squre3[4] - num;
		squre3[5] = squre3[5] - num;
		squre3[6] = squre3[6] + num;
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x > 400 && y > 400) && (x < 800 && y < 800)) {
		squre3[3] = squre3[3] - num;
		squre3[4] = squre3[4] + num;
		squre3[5] = squre3[5] + num;
		squre3[6] = squre3[6] - num;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre4[3] * 400 && y > 400 - squre4[4] * 400) && (x < 400 + squre4[5] * 400 && y < 400 - squre4[6] * 400)) {
		squre4[3] = squre4[3] + num;
		squre4[4] = squre4[4] - num;
		squre4[5] = squre4[5] - num;
		squre4[6] = squre4[6] + num;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN &&
		(x > 0 && y > 400) && (x < 400 && y < 800)) {
		squre4[3] = squre4[3] - num;
		squre4[4] = squre4[4] + num;
		squre4[5] = squre4[5] + num;
		squre4[6] = squre4[6] - num;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre1[3] * 400 && y > 400 - squre1[4] * 400) && (x < 400 + squre1[5] * 400 && y < 400 - squre1[6] * 400)) {
		squre1[0] = (rand() % 10+1) / 10.0;
		squre1[1] = (rand() % 10 + 1) / 10.0;
		squre1[2] = (rand() % 10 + 1) / 10.0;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 0 && y > 0) && (x < 400 && y < 400)) {
		backcolor[0] = (rand() % 10 + 1) / 10.0;
		backcolor[1] = (rand() % 10 + 1) / 10.0;
		backcolor[2] = (rand() % 10 + 1) / 10.0;
		backcolor[3] = (rand() % 10 + 1) / 10.0;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre2[3] * 400 && y > 400 - squre2[4] * 400) && (x < 400 + squre2[5] * 400 && y < 400 - squre2[6] * 400)) {
		squre2[0] = (rand() % 10 + 1) / 10.0;
		squre2[1] = (rand() % 10 + 1) / 10.0;
		squre2[2] = (rand() % 10 + 1) / 10.0;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 400 && y > 0) && (x < 800 && y < 400)) {
		backcolor[0] = (rand() % 10 + 1) / 10.0;
		backcolor[1] = (rand() % 10 + 1) / 10.0;
		backcolor[2] = (rand() % 10 + 1) / 10.0;
		backcolor[3] = (rand() % 10 + 1) / 10.0;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre3[3] * 400 && y > 400 - squre3[4] * 400) && (x < 400 + squre3[5] * 400 && y < 400 - squre3[6] * 400)) {
		squre3[0] = (rand() % 10 + 1) / 10.0;
		squre3[1] = (rand() % 10 + 1) / 10.0;
		squre3[2] = (rand() % 10 + 1) / 10.0;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 400 && y > 400) && (x < 800 && y < 800)) {
		backcolor[0] = (rand() % 10 + 1) / 10.0;
		backcolor[1] = (rand() % 10 + 1) / 10.0;
		backcolor[2] = (rand() % 10 + 1) / 10.0;
		backcolor[3] = (rand() % 10 + 1) / 10.0;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 400 + squre4[3] * 400 && y > 400 - squre4[4] * 400) && (x < 400 + squre4[5] * 400 && y < 400 - squre4[6] * 400)) {
		squre4[0] = (rand() % 10 + 1) / 10.0;
		squre4[1] = (rand() % 10 + 1) / 10.0;
		squre4[2] = (rand() % 10 + 1) / 10.0;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
		(x > 0 && y > 400) && (x < 400 && y < 800)) {
		backcolor[0] = (rand() % 10 + 1) / 10.0;
		backcolor[1] = (rand() % 10 + 1) / 10.0;
		backcolor[2] = (rand() % 10 + 1) / 10.0;
		backcolor[3] = (rand() % 10 + 1) / 10.0;
	}
}

void squre() {
	glClearColor(backcolor[0], backcolor[1], backcolor[2], backcolor[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(squre1[0], squre1[1], squre1[2]);
	glRectf(squre1[3], squre1[4], squre1[5], squre1[6]);

	glColor3f(squre2[0], squre2[1], squre2[2]);
	glRectf(squre2[3], squre2[4], squre2[5], squre2[6]);

	glColor3f(squre3[0], squre3[1], squre3[2]);
	glRectf(squre3[3], squre3[4], squre3[5], squre3[6]);

	glColor3f(squre4[0], squre4[1], squre4[2]);
	glRectf(squre4[3], squre4[4], squre4[5], squre4[6]);
	glutSwapBuffers();
}