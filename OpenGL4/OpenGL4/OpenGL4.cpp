#include "Header.h"
#include "CallBack.h"

void main(int argc, char** argv) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Example2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unalble to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initiallized\n";
	}
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);
	glutMainLoop();
}