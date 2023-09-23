#include "Header.h"
#include "CallBack.h"

int width, height;

void main(int argc, char** argv) {

	width = 1000;
	height = 1000;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example6");

	glewExperimental = GL_TRUE;
	glewInit();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();

}