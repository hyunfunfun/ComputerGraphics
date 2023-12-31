﻿#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <stdlib.h>
#include <random>
#include <fstream>
#include <iterator>
#include <time.h>

struct Shape {
	GLuint vbo[2], vao, ebo;
};

Shape s[2];

//정육면체
GLfloat vertex[][3] = {
    { -0.2, 0.2, -0.2 }, //0
    { -0.2, 0.2, 0.2 }, //1
    { 0.2, 0.2, 0.2 }, //2

	{ -0.2, 0.2, -0.2 }, //0
	{ 0.2, 0.2, 0.2 }, //2
	{ 0.2, 0.2, -0.2 },//3

	{ -0.2, -0.2, -0.2 },//4
	{ -0.2, -0.2, 0.2 },//5
	{ 0.2, -0.2, 0.2 },//6

	{ -0.2, -0.2, -0.2 },//4
	{ 0.2, -0.2, 0.2 },//6
	{ 0.2, -0.2, -0.2 },//7

	{ -0.2, 0.2, 0.2 }, //1
	{ -0.2, 0.2, -0.2 }, //0
	{ -0.2, -0.2, -0.2 },//4

	{ -0.2, 0.2, 0.2 }, //1
	{ -0.2, -0.2, -0.2 },//4
	{ -0.2, -0.2, 0.2 },//5

	{ 0.2, 0.2, 0.2 }, //2
	{ 0.2, -0.2, -0.2 },//7
	{ 0.2, 0.2, -0.2 },//3

	{ 0.2, 0.2, 0.2 }, //2
	{ 0.2, -0.2, 0.2 },//6
	{ 0.2, -0.2, -0.2 },//7

	{ -0.2, 0.2, -0.2 }, //0
	{ 0.2, 0.2, -0.2 },//3
	{ -0.2, -0.2, -0.2 },//4

	{ 0.2, 0.2, -0.2 },//3
	{ 0.2, -0.2, -0.2 },//7
	{ -0.2, -0.2, -0.2 },//4

	{ -0.2, 0.2, 0.2 }, //1
	{ -0.2, -0.2, 0.2 },//5
	{ 0.2, -0.2, 0.2 },//6

	{ -0.2, 0.2, 0.2 }, //1
	{ 0.2, -0.2, 0.2 },//6
	{ 0.2, 0.2, 0.2 }, //2
};

GLfloat colors[][3] = {
    { 0.1, 0.6, 1.0 }, 
	{ 0.1, 0.6, 1.0 }, 
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
	{ 0.1, 0.6, 1.0 },
};

unsigned int index[] = {
	0,1,2,
	0,2,3,
	4,5,6,
	4,6,7,
	1,0,4,
	1,4,5,
	2,7,3,
	2,6,7,
	0,3,4,
	3,7,4,
	1,5,6,
	1,6,2
};

//사면체
GLfloat vertex1[][3] = {
	{-0.2,0.0,0.0}, //0
	{0.2,0.0,0.0}, //1
	{0.0,0.0,0.5}, //2

	{-0.2,0.0,0.0}, //0
	{0.0,0.0,0.5}, //2
	{0.0,0.5,0.0},//3

	{0.2,0.0,0.0}, //1
	{0.0,0.5,0.0},//3
	{0.0,0.0,0.5}, //2

	{0.2,0.0,0.0}, //1
	{-0.2,0.0,0.0}, //0
	{0.0,0.5,0.0},//3
};

GLfloat colors1[][3] = {
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
	 { 0.1, 0.6, 1.0 },
};



int face = 0;
int faceof = 0;

int ran = 0;
int ran1 = 0;

int mode = 0;


GLfloat rColor = 0, gColor = 0, bColor = 0;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void Draw();

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

int main(int argc, char** argv) {

	srand(time(NULL));

    glutInit(&argc, argv);
	width = 800, height = 600;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Cube");
	glewExperimental = GL_TRUE;
	glewInit();

	/*초기화 함수*/
	make_shaderProgram();
	Initvbovao();
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);

	Initvbovao();
    glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	Tx = glm::translate(Tx, glm::vec3(0.0, 0.0, 0.0)); //--- x축으로 이동 행렬
	Rz = glm::rotate(Rz, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	Rz = glm::rotate(Rz, glm::radians(-10.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬

	TR = Tx * Rz; //--- 합성 변환 행렬: 회전  이동

	//vertex.glsl에 modelTransform에 좌표를 넣기 때문에 전처럼 updatebuffer()함수(vao,vbo업데이트)함수를 쓰지 않아도 된다.
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변


	glUseProgram(shaderProgramID);
	
	
	/*vao vbo 자동 업데이트*/
	/*그리기*/
	Draw();

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	{
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	{
		glGenVertexArrays(1, &s[1].vao);
		glGenBuffers(2, s[1].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	if (mode==2) {
		glBindVertexArray(s[1].vao);

		glDrawArrays(GL_TRIANGLES, faceof, face);
	}
	if (mode==1) {
		glBindVertexArray(s[0].vao);

		glDrawArrays(GL_TRIANGLES, faceof, face);
	}
	if (mode == 3) {
		glBindVertexArray(s[0].vao);

		glDrawArrays(GL_TRIANGLES, ran, face);
		glDrawArrays(GL_TRIANGLES, ran1, face);
	}

	if (mode == 4) {
		glBindVertexArray(s[1].vao);

		glDrawArrays(GL_TRIANGLES, ran, face);
		glDrawArrays(GL_TRIANGLES, ran1, face);
	}


	//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)0);
	//glDisableVertexAttribArray(PosLocation);
	//glDisableVertexAttribArray(ColorLocation);

}

void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		mode = 1;
		face = 6;
		faceof = 0;
		glutPostRedisplay();
		break;
	case '2':
		mode = 1;
		face = 6;
		faceof = 6;
		glutPostRedisplay();
		break;
	case '3':
		mode = 1;
		face = 6;
		faceof = 12;
		glutPostRedisplay();
		break;
	case '4':
		mode = 1;
		face = 6;
		faceof = 18;
		glutPostRedisplay();
		break;
	case '5':
		mode = 1;
		face = 6;
		faceof = 24;
		glutPostRedisplay();
		break;
	case '6':
		mode = 1;
		face = 6;
		faceof = 30;
		glutPostRedisplay();
		break;
	case '7':
		mode = 2;
		face = 3;
		faceof = 0;
		glutPostRedisplay();
		break;
	case '8':
		mode = 2;
		face = 3;
		faceof = 3;
		glutPostRedisplay();
		break;
	case '9':
		mode = 2;
		face = 3;
		faceof = 6;
		glutPostRedisplay();
		break;
	case '0':
		mode = 2;
		face = 3;
		faceof = 9;
		glutPostRedisplay();
		break;
	case 'c':
		mode = 3;
		face = 6;
		ran = (rand() % 6) * 6;
		ran1 = (rand() % 6) * 6;
		while (ran == ran1) {
			ran1 = (rand() % 6) * 6;
		}
		glutPostRedisplay();
		break;
	case 't':
		mode = 4;
		face = 3;
		ran = (rand() % 4) * 3;
		ran1 = (rand() % 4) * 3;
		while (ran == ran1) {
			ran1 = (rand() % 4) * 3;
		}
		glutPostRedisplay();
		break;
	}
}