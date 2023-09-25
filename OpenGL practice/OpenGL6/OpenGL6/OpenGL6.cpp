#include "Header.h"
#include "CallBack.h"

int width, height;

void main(int argc, char** argv) {

	width = 1000;
	height = 1000;
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Example6");

	glewExperimental = GL_TRUE;
	glewInit();


	defrect();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

}