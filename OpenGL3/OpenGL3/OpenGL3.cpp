#include "Header.h"

GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Movesqure(int x, int y);
void Mouse(int button, int state, int x, int y);

bool button_down = false;

float winx = 900;
float winy = 600;
float rectx = 0.0f;
float recty = 0.0f;
float rectsize = 0.1f;
float squre1[4] = { -(winy / winx)*rectsize, (winx / winy)*rectsize, (winy / winx)*rectsize, -(winx / winy)*rectsize };



float winx = 1000;
float winy = 1000;
float squresize = 0.1;
float squre1[7] = {(winx/winx)-1-squresize,(winy / winy - 1) - squresize ,(winx / winx) - 1 + squresize ,(winy / winy) - 1 + squresize ,1.0f, 0.5f, 0.1f };

void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winx, winy);
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
	glutMouseFunc(Mouse);
	glutMotionFunc(Movesqure);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1f, 0.5f, 0.5f);
	glColor3f(squre1[4], squre1[5], squre1[6]);
	glRectf(squre1[0], squre1[1], squre1[2], squre1[3]);
	glutSwapBuffers();
}
void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		button_down = true;
	}
}
int prevx=0;
int prevy=0;
void Movesqure(int x, int y) {
	if (button_down == true) {
		rectx -= ((float)(prevx-x) / 2000);
		recty += ((float)(prevy-y) / 2000);
		prevx = x;
		prevy = y;
	}

}
