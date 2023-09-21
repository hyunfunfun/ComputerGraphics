#include "Header.h"

GLvoid drawScene(GLvoid);
void Reshape(int w, int h);
void Movesqure(int x, int y);
void Mouse(int button, int state, int x, int y);

bool button_down = false;
float prevx;
float prevy;
float COx = 0.0f;
float COy = 0.0f;
float rectsize = 0.1f;
float squre1[4] = { COx-rectsize, COy-rectsize, COx+rectsize, COy+rectsize };


void main(int argc, char **argv) {
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
	glutSwapBuffers();
}
void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / 500) - 1;
	float ogy = -(((float)y / 500) - 1);
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN&& ogx > squre1[0] && ogx <squre1[2] && ogy >squre1[1] && ogy < squre1[3]) {
		prevx = ogx;
		prevy = ogy;
		button_down = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		button_down = false;
		prevx = ogx;
		prevy = ogy;
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

}
