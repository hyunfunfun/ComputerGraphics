#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLuint vbo[2], vao, ebo;
};

struct Cube {
	GLfloat cubevertex[6][3] = { 0 };
	GLfloat cubecolors[6][3] = { 0 };

	GLuint vbo[2], vao, ebo;
};

struct Cone {
	GLfloat conevertex[6][3] = { 0 };
	GLfloat conecolors[6][3] = { 0 };
	GLuint vbo[2], vao, ebo;
};



Shape s;
Cube c[6];
Cone o[5];

//정육면체
GLfloat vertex[][3] = {
	{ -0.2, 0.2, -0.2 }, //0
	{ -0.2, 0.2, 0.2 }, //1
	{ 0.2, 0.2, 0.2 }, //2

	{ -0.2, 0.2, -0.2 }, //0
	{ 0.2, 0.2, 0.2 }, //2
	{ 0.2, 0.2, -0.2 },//3

	{ -0.2, -0.2, -0.2 },//4
	{ 0.2, -0.2, 0.2 },//6
	{ -0.2, -0.2, 0.2 },//5

	{ -0.2, -0.2, -0.2 },//4
	{ 0.2, -0.2, -0.2 },//7
	{ 0.2, -0.2, 0.2 },//6

	{ -0.2, 0.2, -0.2 }, //0
	{ 0.2, 0.2, -0.2 },//3
	{ -0.2, -0.2, -0.2 },//4

	{ 0.2, 0.2, -0.2 },//3
	{ 0.2, -0.2, -0.2 },//7
	{ -0.2, -0.2, -0.2 },//4

	{ -0.2, 0.2, 0.2 }, //1
	{ -0.2, -0.2, 0.2 },//5
	{ 0.2, 0.2, 0.2 }, //2

	{ 0.2, -0.2, 0.2 },//6
	{ 0.2, 0.2, 0.2 }, //2
	{ -0.2, -0.2, 0.2 },//5

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


};

GLfloat colors[][3] = {

	{ 0.0, 1.0, 0.0 }, //0
	{ 0.5, 0.5, 1.0 }, //1
	{ 0.0, 0.0, 0.0 }, //2

	{ 0.0, 1.0, 0.0 }, //0
	{ 0.0, 0.0, 0.0 }, //2
	{ 1.0, 1.0, 0.0 }, //3

	{ 0.0, 0.0, 0.0 }, //4
	{ 1.0, 0.0, 1.0 }, //6
	{ 0.0, 0.0, 1.0 }, //5

	{ 0.0, 0.0, 0.0 }, //4
	{ 1.0, 0.0, 0.0 }, //7
	{ 1.0, 0.0, 1.0 }, //6

	{ 0.0, 1.0, 0.0 }, //0
	{ 1.0, 1.0, 0.0 }, //3
	{ 0.0, 0.0, 0.0 }, //4

	{ 1.0, 1.0, 0.0 }, //3
	{ 1.0, 0.0, 0.0 }, //7
	{ 0.0, 0.0, 0.0 }, //4

	{ 0.5, 0.5, 1.0 }, //1
	{ 0.0, 0.0, 1.0 }, //5
	{ 0.0, 0.0, 0.0 }, //2

	{ 1.0, 0.0, 1.0 }, //6
	{ 0.0, 0.0, 0.0 }, //2
	{ 0.0, 0.0, 1.0 }, //5

	{ 0.5, 0.5, 1.0 }, //1
	{ 0.0, 1.0, 0.0 }, //0
	{ 0.0, 0.0, 0.0 }, //4

	{ 0.5, 0.5, 1.0 }, //1
	{ 0.0, 0.0, 0.0 }, //4
	{ 0.0, 0.0, 1.0 }, //5

	{ 0.0, 0.0, 0.0 }, //2
	{ 1.0, 0.0, 0.0 }, //7
	{ 1.0, 1.0, 0.0 }, //3

	{ 0.0, 0.0, 0.0 }, //2
	{ 1.0, 0.0, 1.0 }, //6
	{ 1.0, 0.0, 0.0 }, //7


};

//사면체
GLfloat vertex1[][3] = {
	{-0.2,-0.2,-0.2}, //0
	{0.2,-0.2,0.2},  //2
	{-0.2,-0.2,0.2}, //1

	{-0.2,-0.2,-0.2}, //0
	{0.2,-0.2,-0.2},  //3
	{0.2,-0.2,0.2},  //2

	{-0.2,-0.2,0.2}, //1
	{0.2,-0.2,0.2},  //2
	{0.0,0.4,0.0},  //4

	{-0.2,-0.2,-0.2}, //0
	{0.0,0.4,0.0},  //4
	{0.2,-0.2,-0.2},  //3

	{-0.2,-0.2,-0.2}, //0
	{-0.2,-0.2,0.2}, //1
	{0.0,0.4,0.0},  //4


	{0.2,-0.2,0.2},  //2
	{0.2,-0.2,-0.2},  //3
	{0.0,0.4,0.0},  //4
};

GLfloat colors1[][3] = {
	 { 0.0, 0.0, 0.0 }, //0
	 { 0.0, 1.0, 0.0 },	//2
	 { 1.0, 0.0, 0.0 },	//1

	 { 0.0, 0.0, 0.0 },	//0
	 { 0.0, 0.0, 1.0 },	//3
	 { 0.0, 1.0, 0.0 },	//2

	 { 1.0, 0.0, 0.0 },	//1
	 { 0.0, 1.0, 0.0 },	//2
	 { 1.0, 1.0, 0.0 },	//4

	 { 0.0, 0.0, 0.0 },	//0
	 { 1.0, 1.0, 0.0 },	//4
	 { 0.0, 0.0, 1.0 },	//3

	 { 0.0, 0.0, 0.0 },	//0
	 { 1.0, 0.0, 0.0 },	//1
	 { 1.0, 1.0, 0.0 },	//4

	 { 0.0, 1.0, 0.0 },	//2
	 { 0.0, 0.0, 1.0 },	//3
	 { 1.0, 1.0, 0.0 },	//4
};
float xRotateAni = 20.0f;
float yRotateAni = 20.0f;
float xRotateAni1 = 20.0f;
float yRotateAni1 = 20.0f;
float xRotateAni2 = 20.0f;
float yRotateAni2 = 20.0f;
float xRotateAni3 = 20.0f;
float yRotateAni3 = 20.0f;
float xRotateAni4 = 20.0f;
float yRotateAni4 = 20.0f;
float xRotateAni5 = 20.0f;
float yRotateAni5 = 20.0f;
float xRotateAni6 = 20.0f;
float yRotateAni6 = 20.0f;

float up = 0.0f;
double xMove = 0.0, yMove = 0.0, zMove = 0.0;
double xMove1 = 0.0, yMove1 = 0.0, zMove1 = 0.0;
double xMove2 = 0.0, yMove2 = 0.0, zMove2 = 0.0;
double xMove3 = 0.0, yMove3 = 0.0, zMove3 = 0.0;
double xMove4 = 0.0, yMove4 = 0.0, zMove4 = 0.0;
double xMove5 = 0.0, yMove5 = 0.0, zMove5 = 0.0;
double xMove6 = 0.0, yMove6 = 0.0, zMove6 = 0.0;

bool ttimer = false;
bool ftimer = false;
bool stimer = false;

bool pcheck = false;

bool culling = false;

GLfloat line[][3] = {
	{0.0,1.0,0.0},
	{0.0,-1.0,0.0},
	{-1.0,0.0,0.0},
	{1.0,0.0,0.0},
	{0.0,0.0,1.0},
	{0.0,0.0,-1.0},
};
GLfloat linecolors[][3] = {
	{1.0,1.0,1.0},
	{1.0,1.0,1.0},
	{1.0,1.0,1.0},
	{1.0,1.0,1.0},
	{1.0,1.0,1.0},
	{1.0,1.0,1.0}
};
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
GLvoid Timer(int value);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Setcube();
void Initvbovao();
void Draw_cube_1();
void Draw_cube_2();
void Draw_cube_3();
void Draw_cube_4();
void Draw_cube_5();
void Draw_cube_6();
void Drawline();

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
	Setcube();
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

	glEnable(GL_DEPTH_TEST);
	culling ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

	glUseProgram(shaderProgramID);
	glm::mat4 projection = glm::mat4(1.0f);
	if(pcheck==false)
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	else if (pcheck == true) {
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	}
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);



	/*그리기*/
	Draw_cube_1();
	Draw_cube_2();
	Draw_cube_3();
	Draw_cube_4();
	Draw_cube_5();
	Draw_cube_6();

	Drawline();
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Setcube() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			c[i].cubevertex[j][0] = vertex[i * 6 + j][0];
			c[i].cubevertex[j][1] = vertex[i * 6 + j][1];
			c[i].cubevertex[j][2] = vertex[i * 6 + j][2];
			c[i].cubecolors[j][0] = colors[i * 6 + j][0];
			c[i].cubecolors[j][1] = colors[i * 6 + j][1];
			c[i].cubecolors[j][2] = colors[i * 6 + j][2];
		}
	}
}

void Initvbovao()
{

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	for(int i=0;i<6;i++)
	{
		glGenVertexArrays(1, &c[i].vao);
		glGenBuffers(2, c[i].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(c[i].vao);

		glBindBuffer(GL_ARRAY_BUFFER, c[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(c[i].cubevertex), c[i].cubevertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, c[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(c[i].cubecolors), c[i].cubecolors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);

		
	}
	
	for (int i = 0; i < 5; i++)
	{
		glGenVertexArrays(1, &o[i].vao);
		glGenBuffers(2, o[i].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(o[i].vao);

		glBindBuffer(GL_ARRAY_BUFFER, o[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, o[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	{
		glGenVertexArrays(1, &s.vao);
		glGenBuffers(2, s.vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s.vao);

		glBindBuffer(GL_ARRAY_BUFFER, s.vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s.vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolors), linecolors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void Draw_cube_1()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	Tx = glm::translate(Tx, glm::vec3(xMove1, yMove1, zMove1)); //--- x축으로 이동 행렬
	Rz = glm::rotate(Rz, glm::radians(xRotateAni +xRotateAni1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	Rz = glm::rotate(Rz, glm::radians(yRotateAni +yRotateAni1), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
	if (ttimer == true) {
		TR = Rz * Tx * Sx;
	}
	else
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[0].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Draw_cube_2()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	for (int i = 0; i < 6; i++) {
		glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
		glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

		Tx = glm::translate(Tx, glm::vec3(xMove2, yMove2, zMove2)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(xRotateAni +xRotateAni2), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(yRotateAni +yRotateAni2), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(c[1].vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void Draw_cube_3()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	for (int i = 0; i < 6; i++) {
		glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
		glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

		Tx = glm::translate(Tx, glm::vec3(xMove3, yMove3, zMove3)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(xRotateAni +xRotateAni3), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(yRotateAni +yRotateAni3), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(c[2].vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void Draw_cube_4()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	for (int i = 0; i < 6; i++) {
		glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
		glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

		Tx = glm::translate(Tx, glm::vec3(xMove4, yMove4, zMove4)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(xRotateAni +xRotateAni4), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(yRotateAni +yRotateAni4), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(c[3].vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void Draw_cube_5()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	for (int i = 0; i < 6; i++) {
		glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
		glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

		Tx = glm::translate(Tx, glm::vec3(xMove5, yMove5, zMove5)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(xRotateAni +xRotateAni5), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(yRotateAni +yRotateAni5), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(c[4].vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void Draw_cube_6()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	for (int i = 0; i < 6; i++) {
		glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
		glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
		glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

		Tx = glm::translate(Tx, glm::vec3(xMove6, yMove6, zMove6)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(xRotateAni + xRotateAni6), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(yRotateAni + yRotateAni6), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(c[5].vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}


void Drawline()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{//line
		Tx = glm::translate(Tx, glm::vec3(0, 0, 0)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(2, 2, 2)); //--- x축으로 이동 행렬
		TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s.vao);
		glLineWidth(1);
		glDrawArrays(GL_LINES, 0, 6);

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

GLvoid Timer(int value) {
	
	if (ttimer == true) {
		xRotateAni1 += 1;
		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
	}
	if (ftimer == true) {
		xRotateAni4 += 1;
		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
	}
	if (stimer == true) {
		yMove5 += 0.01;
		yMove6 += 0.01;
		
		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
	}
}


GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'h':
		culling ? culling = false : culling = true;
		break;
	case 'y':
		yRotateAni += 1;
		break;
	case 't':
		ttimer ? ttimer = false : ttimer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'f':
		ftimer ? ftimer = false : ftimer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	case 's':
		stimer ? stimer = false : stimer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'p':
		pcheck ? pcheck = false : pcheck = true;
		break;
	}
	glutPostRedisplay();
}