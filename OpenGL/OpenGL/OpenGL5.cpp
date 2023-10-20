#include "Header.h"
#include "Callback2.h"

int width, height;

void main(int argc, char** argv) {

	width = 1000;
	height = 1000;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example5");

	glewExperimental = GL_TRUE;
	glewInit();
	defsqure();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

}