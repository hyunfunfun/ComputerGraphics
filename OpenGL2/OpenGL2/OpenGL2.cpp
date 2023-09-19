#include "Header.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
//GLvoid Mouse(int button, int state, int x, int y);

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(250, 250);
	glutCreateWindow("Example2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unalble to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initiallized\n";
	}
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	//glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}