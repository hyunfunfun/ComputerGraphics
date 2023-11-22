#include "function.h"
#include <iostream>

int main(int argc, char** argv)
{
	/***********************************
	[순서]
	1.윈도우를 생성한다.
	2.2.0이상 확장 기능을 사용하기 위해 GLEW를 현재 버전으로 초기화한다
	3.다양한 콜백 함수들을 호출한다.
	***********************************/

	/*********윈도우 생성하기*********/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(550, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Drill25");

	/*********GLEW 초기화하기*********/
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	/***********시작 초기화***********/
	/*셰이더 프로그램*/
	make_shaderProgram();
	/*객체 초기화*/
	InitObject();
	/*vao에 vbo연결하기*/
	InitBuffer();
	/*그 외*/
	glEnable(GL_DEPTH_TEST); //은면 제거
	printf("[n]:큐브/피라미드\n");
	printf("[m]:조명 켜기/끄기\n");
	printf("[y]:센터 큐브를 y축에 대하여 회전(제자리 회전)\n");
	printf("[r]:조명 큐브를 센터 큐브를 중심 y축에 대하여 양/음 방향으로 공전(궤도: 원)\n");
	printf("[z/Z]:조명 큐브를 센터 큐브에 가깝게/멀게 이동하기(조명의 위치가 멀어지면 공전 궤도도 함꼐 멀어짐\n");
	printf("[q]:프로그램 종료\n");
	/*********콜백 함수(운영체제 호출 함수) 호출하기*********/

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();

	return 0;
}
