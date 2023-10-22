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
	{ -0.4, 0.4, -0.4 }, //0
	{ -0.4, 0.4, 0.4 }, //1
	{ 0.4, 0.4, 0.4 }, //2

	{ -0.4, 0.4, -0.4 }, //0
	{ 0.4, 0.4, 0.4 }, //2
	{ 0.4, 0.4, -0.4 },//3

	{ -0.4, -0.4, -0.4 },//4
	{ 0.4, -0.4, 0.4 },//6
	{ -0.4, -0.4, 0.4 },//5

	{ -0.4, -0.4, -0.4 },//4
	{ 0.4, -0.4, -0.4 },//7
	{ 0.4, -0.4, 0.4 },//6

	{ -0.4, 0.4, -0.4 }, //0
	{ 0.4, 0.4, -0.4 },//3
	{ -0.4, -0.4, -0.4 },//4

	{ 0.4, 0.4, -0.4 },//3
	{ 0.4, -0.4, -0.4 },//7
	{ -0.4, -0.4, -0.4 },//4

	{ -0.4, 0.4, 0.4 }, //1
	{ -0.4, -0.4, 0.4 },//5
	{ 0.4, 0.4, 0.4 }, //2

	{ 0.4, -0.4, 0.4 },//6
	{ 0.4, 0.4, 0.4 }, //2
	{ -0.4, -0.4, 0.4 },//5

	{ -0.4, 0.4, 0.4 }, //1
	{ -0.4, 0.4, -0.4 }, //0
	{ -0.4, -0.4, -0.4 },//4

	{ -0.4, 0.4, 0.4 }, //1
	{ -0.4, -0.4, -0.4 },//4
	{ -0.4, -0.4, 0.4 },//5

	{ 0.4, 0.4, 0.4 }, //2
	{ 0.4, -0.4, -0.4 },//7
	{ 0.4, 0.4, -0.4 },//3

	{ 0.4, 0.4, 0.4 }, //2
	{ 0.4, -0.4, 0.4 },//6
	{ 0.4, -0.4, -0.4 },//7


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
	{-0.4,-0.4,-0.4}, //0
	{0.4,-0.4,0.4},  //2
	{-0.4,-0.4,0.4}, //1

	{-0.4,-0.4,-0.4}, //0
	{0.4,-0.4,-0.4},  //3
	{0.4,-0.4,0.4},  //2

	{-0.4,-0.4,0.4}, //1
	{0.4,-0.4,0.4},  //2
	{0.0,0.6,0.0},  //4

	{-0.4,-0.4,-0.4}, //0
	{0.0,0.6,0.0},  //4
	{0.4,-0.4,-0.4},  //3

	{-0.4,-0.4,-0.4}, //0
	{-0.4,-0.4,0.4}, //1
	{0.0,0.6,0.0},  //4


	{0.4,-0.4,0.4},  //2
	{0.4,-0.4,-0.4},  //3
	{0.0,0.6,0.0},  //4
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

float xRotateAni1 = 0.0f;
float xRotateAni4 = 0.0f;

float coneRotate1 = 0.0f;
float coneRotate2 = 0.0f;
float coneRotate3 = 0.0f;
float coneRotate4 = 0.0f;

double xMove = 0.0, yMove = 0.0, zMove = 0.0;
double yMove5 = 0.0;
double yMove6 = 0.0;
double xscale3 = 1.0;
double yscale3 = 1.0;
double zscale3 = 1.0;


bool timer = false;
//f
bool ttimer = false;

//f
bool ftimer = false;
bool fcheck = false;

//s
bool stimer = false;
bool scheck = false;

//b
bool btimer = false;
bool bcheck = false;


//o
bool otimer = false;
bool ocheck = false;

//r
bool rtimer = false;
bool rcheck = false;
int rmode = 1;

bool pcheck = false;


bool object = false;
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
void Setpyramid();
void Initvbovao();
void Draw_cube_1();
void Draw_cube_2();
void Draw_cube_3();
void Draw_cube_4();
void Draw_cube_5();
void Draw_cube_6();

void Draw_cone_1();
void Draw_cone_2();
void Draw_cone_3();
void Draw_cone_4();
void Draw_cone_5();
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
	Setpyramid();
	Initvbovao();

	cout << "0:물체변경\n h: 은면제거 설정\n/ 해제  y : y축에 대하여 자전한다" << endl;

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
	if(object==false)
	{
		Draw_cube_1();
		Draw_cube_2();
		Draw_cube_3();
		Draw_cube_4();
		Draw_cube_5();
		Draw_cube_6();
	}
	else {
		Draw_cone_1();
		Draw_cone_2();
		Draw_cone_3();
		Draw_cone_4();
		Draw_cone_5();
	}

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

void Setpyramid() {
	for (int j = 0; j < 6; j++) {
		o[0].conevertex[j][0] = vertex1[j][0];
		o[0].conevertex[j][1] = vertex1[j][1];
		o[0].conevertex[j][2] = vertex1[j][2];
		o[0].conecolors[j][0] = colors1[j][0];
		o[0].conecolors[j][1] = colors1[j][1];
		o[0].conecolors[j][2] = colors1[j][2];
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			o[i+1].conevertex[j][0] = vertex1[6 + (i*3+j)][0];
			o[i+1].conevertex[j][1] = vertex1[6 + (i*3+j)][1];
			o[i+1].conevertex[j][2] = vertex1[6 + (i*3+j)][2];
			o[i+1].conecolors[j][0] = colors1[6 + (i*3+j)][0];
			o[i+1].conecolors[j][1] = colors1[6 + (i*3+j)][1];
			o[i+1].conecolors[j][2] = colors1[6 + (i*3+j)][2];
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(o[i].conevertex), o[i].conevertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, o[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(o[i].conecolors), o[i].conecolors, GL_STATIC_DRAW);
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

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	
	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove + 0.4, zMove)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(xRotateAni1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove - 0.4, zMove)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[0].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Draw_cube_2()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::translate(TR, glm::vec3(xMove, yMove, zMove)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[1].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}
void Draw_cube_3()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove, zMove)); //--- x축으로 이동 행렬
	TR = glm::scale(TR, glm::vec3(xscale3, yscale3, 1.0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[2].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}
void Draw_cube_4()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove-0.4, zMove+0.4)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(xRotateAni4), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove+0.4, zMove - 0.4)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[3].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Draw_cube_5()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove5, zMove)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[4].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}
void Draw_cube_6()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove6, zMove)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(c[5].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Draw_cone_1()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기


	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::translate(TR, glm::vec3(xMove, yMove, zMove)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(o[0].vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
}

void Draw_cone_2()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove-0.4, zMove+0.4)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(coneRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove+0.4, zMove-0.4)); //--- x축으로 이동 행렬

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(o[1].vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
}
void Draw_cone_3()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove - 0.4, zMove-0.4)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(coneRotate2), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove, yMove + 0.4, zMove+0.4)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(o[2].vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
}
void Draw_cone_4()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove-0.4, yMove - 0.4, zMove)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(coneRotate3), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove+0.4, yMove + 0.4, zMove)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(o[3].vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void Draw_cone_5()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	TR = glm::rotate(TR, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove + 0.4, yMove - 0.4, zMove)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(coneRotate4), glm::vec3(0.0, 0.0, 1.0)); //--- x축에 대하여 회전 행렬
	TR = glm::translate(TR, glm::vec3(xMove - 0.4, yMove + 0.4, zMove)); //--- x축으로 이동 행렬
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

	glBindVertexArray(o[4].vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
	}
	if (ftimer == true) {
		if (fcheck == false) {
			xRotateAni4 -= 1;
			if (xRotateAni4 < 0)
				fcheck = true;
		}
		else {
			xRotateAni4 += 1;
			if (xRotateAni4 > 90)
				fcheck = false;
		}
	}
	if (stimer == true) {
		if (scheck == false) {
			yMove5 += 0.01;
			yMove6 += 0.01;
			if (yMove5 > 1.0)
				scheck = true;
		}
		else {
			yMove5 -= 0.01;
			yMove6 -= 0.01;
			if (yMove5 < 0.0)
				scheck = false;
		}
	}
	if (btimer == true) {
		if (scheck == false) {
			xscale3 -= 0.01;
			yscale3 -= 0.01;
			zscale3 -= 0.01;
			if (xscale3 < 0.0)
				scheck = true;
		}
		else {
			xscale3 += 0.01;
			yscale3 += 0.01;
			zscale3 += 0.01;
			if (xscale3 > 1.0)
				scheck = false;
		}
	}
	if (otimer == true) {
		if (ocheck == false) {
			coneRotate1 += 1;
			coneRotate2 -= 1;
			coneRotate3 += 1;
			coneRotate4 -= 1;
			if (coneRotate1 > 220) {
				ocheck = true;
			}
		}
		else {
			coneRotate1 -= 1;
			coneRotate2 += 1;
			coneRotate3 -= 1;
			coneRotate4 += 1;
			if (coneRotate1 < 0) {
				ocheck = false;
			}
		}
	}
	if (rtimer == true) {
		if (rcheck == false) {
			if (rmode == 1) {
				coneRotate1 += 1;
				if (coneRotate1 > 115) {
					rmode = 2;
				}
			}
			if (rmode == 2) {
				coneRotate2 -= 1;
				if (coneRotate2 < -115) {
					rmode = 3;
				}
			}
			if (rmode == 3) {
				coneRotate3 += 1;
				if (coneRotate3 > 115) {
					rmode = 4;
				}
			}
			if (rmode == 4) {
				coneRotate4 -= 1;
				if (coneRotate4 < -115) {
					rmode = 1;
					rcheck = true;
				}
			}
		}
		else {
			if (rmode == 1) {
				coneRotate1 -= 1;
				if (coneRotate1 <= 0) {
					rmode = 2;
				}
			}
			if (rmode == 2) {
				coneRotate2 += 1;
				if (coneRotate2 >= 0) {
					rmode = 3;
				}
			}
			if (rmode == 3) {
				coneRotate3 -= 1;
				if (coneRotate3 <= 0) {
					rmode = 4;
				}
			}
			if (rmode == 4) {
				coneRotate4 += 1;
				if (coneRotate4 >= 0) {
					rmode = 1;
					rcheck = false;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
	
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
		timer ? timer = false : timer = true;
		ttimer ? ttimer = false : ttimer = true;
		ftimer = false;
		stimer = false;
		btimer = false;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'f':
		timer ? timer = false : timer = true;
		ttimer = false;
		ftimer ? ftimer = false : ftimer = true;
		stimer = false;
		btimer = false;
		glutTimerFunc(10, Timer, 1);
		break;
	case 's':
		timer ? timer = false : timer = true;
		ttimer = false;
		ftimer = false;
		stimer ? stimer = false : stimer = true;
		btimer = false;

		glutTimerFunc(10, Timer, 1);
		break;
	case 'b':
		timer ? timer = false : timer = true;
		ttimer = false;
		ftimer = false;
		stimer = false;
		btimer ? btimer = false : btimer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'o':
		timer ? timer = false : timer = true;
		otimer ? otimer = false : otimer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'r':
		timer ? timer = false : timer = true;
		rtimer ? rtimer = false : rtimer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'p':
		pcheck ? pcheck = false : pcheck = true;
		break;
	case '0':
		object ? object = false : object = true;
		break;
	}
	glutPostRedisplay();
}