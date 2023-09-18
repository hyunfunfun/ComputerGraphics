#include "Header.h"



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
	glClearColor((rand() % 10 + 1) / 10.0, (rand() % 10 + 1) / 10.0, (rand() % 10 + 1) / 10.0, (rand() % 10 + 1) / 10.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid drawKScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
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
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) { //--- ������ ����ϰ� �ݹ��Լ� ���� 
	//--- ������ �����ϱ�

	srand(time(NULL));

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0,0); // �������� ��ġ ����
	glutInitWindowSize(800,600); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����(������ �̸�)

	// GLEW �ʱ�ȭ�ϱ�
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
