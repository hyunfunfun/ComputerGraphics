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

void main(int argc, char** argv) { //--- 윈도우 출력하고 콜백함수 설정 
	//--- 윈도우 생성하기

	srand(time(NULL));

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0,0); // 윈도우의 위치 지정
	glutInitWindowSize(800,600); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)

	// GLEW 초기화하기
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
