#define _CRT_SECURE_NO_WARNINGS
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

GLuint vbo[2], vao, ebo;

GLfloat vertex[][3] = {
    { -0.5, 0.5, -0.5 },
    { -0.5, 0.5, 0.5 },
    { 0.5, 0.5, 0.5 },
    { 0.5, 0.5, -0.5 },
    { -0.5, -0.5, -0.5 },
    { -0.5, -0.5, 0.5 },
    { 0.5, -0.5, 0.5 },
    { 0.5, -0.5, -0.5 }
};

GLfloat colors[][3] = {
    { 1.0, 0.0, 0.0 },      // red  
    { 1.0, 1.0, 0.0 },      // yellow  
    { 0.0, 1.0, 0.0 },      // green  
    { 0.0, 0.0, 1.0 },      // blue  
    { 0.5, 0.5, 0.0 },      // gold
    { 1.0, 0.0, 1.0 },      // magenta  
	{ 0.5, 0.5, 0.0 },      // gold
	{ 1.0, 0.0, 0.0 },      // red  
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
	3,7,4
};


GLfloat rColor = 1, gColor = 1, bColor = 1;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);

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
	Rz = glm::rotate(Rz, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); //--- z축에 대하여 회전 행렬
	Rz = glm::rotate(Rz, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0)); //--- z축에 대하여 회전 행렬

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
	glGenVertexArrays(1, &vao);
	glGenBuffers(2, vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glEnableVertexAttribArray(PosLocation);
	glEnableVertexAttribArray(ColorLocation);

}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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