#include "Header.h"

GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Movesqure(int x, int y);
void Mouse(int button, int state, int x, int y);

bool button_down = false;

float winx = 1000;
float winy = 1000;
float rectx = 0.0f;
float recty = 0.0f;
float rectsize = 0.1f;



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
	glClearColor(0.5f, 0.5f, 0.5f, 0.7f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1f, 0.5f, 0.5f);
	glRectf(rectx-rectsize, recty-rectsize, rectx+rectsize, recty+rectsize);
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
void Movesqure(int x, int y) {
	if (button_down == true) {
		rectx += ((float)x / 100000);
		recty += ((float)y / 100000);
	}
}
