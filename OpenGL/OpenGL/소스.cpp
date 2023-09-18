#include "Header.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);



void main(int argc, char** argv) {
	

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(0,0); 
	glutInitWindowSize(800,600); 
	glutCreateWindow("Example1");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}
GLvoid drawScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawCScene() {
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawMScene() {
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawYScene() {
	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawKScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawRandomScene() {
	GLclampf random1 = (rand() % 10 + 1) / 10.0;
	GLclampf random2 = (rand() % 10 + 1) / 10.0;
	GLclampf random3 = (rand() % 10 + 1) / 10.0;
	GLclampf random4 = (rand() % 10 + 1) / 10.0;
	glClearColor(random1, random2, random3, random4);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void TimerFunction(int value) {
	if(value==1) {
		glutTimerFunc(1000, TimerFunction, 1);
	}
	else {
		drawRandomScene();
		glutKeyboardFunc(Keyboard);
		glutTimerFunc(1000, TimerFunction, 0);
	}
}



GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'c':
		glutDisplayFunc(drawCScene);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		break;
	case 'm':
		glutDisplayFunc(drawMScene);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		break;
	case 'y':
		glutDisplayFunc(drawYScene);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		break;
	case 'w':
		glutDisplayFunc(drawScene);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		break;
	case 'k':
		glutDisplayFunc(drawKScene);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		break;
	case 'a':
		glutDisplayFunc(drawRandomScene);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		break;
	case 's':
		glutTimerFunc(1000, TimerFunction, 1);
		break;
	case 't':
		glutTimerFunc(1000, TimerFunction, 0);
		break;
	}
	glutPostRedisplay();
}