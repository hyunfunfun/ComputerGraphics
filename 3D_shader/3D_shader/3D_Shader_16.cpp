﻿#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLuint vbo[2], vao, ebo;
};

Shape s[3];

float colors[] = {
	   0.5f, 0.0f, 0.5f,//4
	   0.0f, 0.0f, 1.0f,//0
	   0.0f, 0.0f, 0.0f,//3

	   0.5f, 0.0f, 0.5f,//4
	   0.0f, 0.0f, 0.0f,//3
	   1.0f, 0.0f, 0.0f,//7

	   0.0f, 1.0f, 0.0f,//2
	   0.5f, 0.5f, 0.0f,//6
	   1.0f, 0.0f, 0.0f,//7

	   0.0f, 1.0f, 0.0f,//2
	   1.0f, 0.0f, 0.0f,//7
	   0.0f, 0.0f, 0.0f,//3

	   0.0f, 0.5f, 0.5f,//1
	   1.0f, 1.0f, 1.0f,//5
	   0.0f, 1.0f, 0.0f,//2

	   1.0f, 1.0f, 1.0f,//5
	   0.5f, 0.5f, 0.0f,//6
	   0.0f, 1.0f, 0.0f,//2

	   0.0f, 0.0f, 1.0f,//0
	   0.5f, 0.0f, 0.5f,//4
	   0.0f, 0.5f, 0.5f,//1

	   0.5f, 0.0f, 0.5f,//4
	   1.0f, 1.0f, 1.0f,//5
	   0.0f, 0.5f, 0.5f,//1

	   0.5f, 0.0f, 0.5f,//4
	   1.0f, 0.0f, 0.0f,//7
	   1.0f, 1.0f, 1.0f,//5

	   1.0f, 0.0f, 0.0f,//7
	   0.5f, 0.5f, 0.0f,//6
	   1.0f, 1.0f, 1.0f,//5

	   0.0f, 0.0f, 1.0f,//0
	   0.0f, 0.5f, 0.5f,//1
	   0.0f, 1.0f, 0.0f,//2

	   0.0f, 0.0f, 1.0f,//0
	   0.0f, 1.0f, 0.0f,//2
	   0.0f, 0.0f, 0.0f,//3
};
GLfloat line[][3] = {
	{0.0,1.0,0.0},
	{0.0,-1.0,0.0},
	{-1.0,0.0,0.0},
	{1.0,0.0,0.0},
	{0.0,0.0,1.0},
	{0.0,0.0,-1.0},
};
GLfloat linecolors[][3] = {
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0}
};

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

bool timer = false;
bool gong = false;
bool obj = false;

float x1RotateAni = 30.0f;
float y1RotateAni = -30.0f;
float x2RotateAni = 30.0f;
float y2RotateAni = -30.0f;
int rotateKey = 0; 
int gongkey = 0;

bool obj1ani = false;
bool obj2ani = false;

double x1move = 0.5;
double x2move = -1.0;

GLfloat rColor = 1, gColor = 1, bColor = 1;

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
void Initvbovao();
void Draw();
void Drawleft();
void Drawright();

char* filetobuf(const char* file)
{
	ifstream in(file, ios_base::binary);

	if (!in) {
		cerr << file << "파일 못찾음";
		exit(1);
	}

	in.seekg(0, ios_base::end);
	long len = in.tellg();
	char* buf = new char[len + 1];
	in.seekg(0, ios_base::beg);

	int cnt = -1;
	while (in >> noskipws >> buf[++cnt]) {}
	buf[len] = 0;

	return buf;
}
bool  Load_Object(const char* path) {
	vertexIndices.clear();
	uvIndices.clear();
	normalIndices.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();

	ifstream in(path);
	if (!in) {
		cerr << path << "파일 못찾음";
		exit(1);
	}

	//vector<char> lineHeader(istream_iterator<char>{in}, {});

	while (in) {
		string lineHeader;
		in >> lineHeader;
		if (lineHeader == "v") {
			glm::vec3 vertex;
			in >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (lineHeader == "vt") {
			glm::vec2 uv;
			in >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		else if (lineHeader == "vn") {
			glm::vec3 normal;
			in >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (lineHeader == "f") {
			char a;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			for (int i = 0; i < 3; i++)
			{
				in >> vertexIndex[i] >> a >> uvIndex[i] >> a >> normalIndex[i];
				vertexIndices.push_back(vertexIndex[i] - 1);
				uvIndices.push_back(uvIndex[i] - 1);
				normalIndices.push_back(normalIndex[i] - 1);
			}
		}
	}

	return true;
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
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);
	
	/*그리기*/
	Draw();
	Drawleft();
	Drawright();

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
	obj ? Load_Object("cone.obj") : Load_Object("cube.obj");

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	{
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);
		glGenBuffers(1, &s[0].ebo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if (obj==false)
		{
			glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[0].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	obj ? Load_Object("cylinder.obj") : Load_Object("sphere.obj");
	{
		glGenVertexArrays(1, &s[1].vao);
		glGenBuffers(1, s[1].vbo);
		glGenBuffers(1, &s[1].ebo);

		glBindVertexArray(s[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[1].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	{//line
		glGenVertexArrays(1, &s[2].vao);
		glGenBuffers(2, s[2].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[2].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolors), linecolors, GL_STATIC_DRAW);
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

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{//line
		Tx = glm::translate(Tx, glm::vec3(0, 0, 0)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = Tx * Rz; //--- 합성 변환 행렬: 회전  이동

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[2].vao);
		glLineWidth(1);
		glDrawArrays(GL_LINES, 0, 6);

	}


	//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)0);
	//glDisableVertexAttribArray(PosLocation);
	//glDisableVertexAttribArray(ColorLocation);

}
void Drawleft() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		Tx = glm::translate(Tx, glm::vec3(-0.5, 0, 0)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(x1RotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(y1RotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(0.5, 0.5, 0.5));
		if(gong==false)
		{
			TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		}
		else if (gong == true) {
			TR = Rz * Tx * Sx; //--- 합성 변환 행렬: 회전  이동
		}

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[0].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 1000, GL_UNSIGNED_INT, 0);
	}
}
void Drawright() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		Tx = glm::translate(Tx, glm::vec3(0.5, 0, 0)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(x2RotateAni), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(y2RotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(0.5, 0.5, 0.5));
		if (gong == false)
		{
			TR = Tx * Rz * Sx; //--- 합성 변환 행렬: 회전  이동
		}
		else if (gong == true) {
			TR = Rz * Tx * Sx; //--- 합성 변환 행렬: 회전  이동
		}

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[1].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, 0);
	}
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

GLvoid Timer(int value){
	if(timer==true)
	{

		glutPostRedisplay(); // 화면 재 출력
		if(gong==false)
		{
			if (obj1ani == true)
			{
				if (rotateKey == 1)
					x1RotateAni += 0.5f;
				if (rotateKey == 2)
					x1RotateAni -= 0.5f;
				if (rotateKey == 3)
					y1RotateAni += 0.5f;
				if (rotateKey == 4)
					y1RotateAni -= 0.5f;
			}
			if (obj2ani == true) {
				if (rotateKey == 1)
					x2RotateAni += 0.5f;
				if (rotateKey == 2)
					x2RotateAni -= 0.5f;
				if (rotateKey == 3)
					y2RotateAni += 0.5f;
				if (rotateKey == 4)
					y2RotateAni -= 0.5f;
			}
		}
		else if (gong == true) {
			if (gongkey == 1) {
				y1RotateAni += 0.5f;
				y2RotateAni += 0.5f;
			}
			if (gongkey == 2) {
				y1RotateAni -= 0.5f;
				y2RotateAni -= 0.5f;
			}
		}
		glutTimerFunc(10, Timer, 1);
	}
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		timer ? timer = false : timer = true;
		rotateKey = 1;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'X':
		timer ? timer = false : timer = true;
		rotateKey = 2;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'y':
		timer ? timer = false : timer = true;
		rotateKey = 3;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'Y':
		timer ? timer = false : timer = true;
		rotateKey = 4;
		glutTimerFunc(10, Timer, 1);
		break;
	case 's':
		timer = false;
		obj = false;
		gong = false;
		Initvbovao();
		rotateKey = 0;
		x1RotateAni = 30.0f;
		y1RotateAni = -30.0f;
		x2RotateAni = 30.0f;
		y2RotateAni = -30.0f;
		break;
	case '1':
		obj1ani = true;
		obj2ani = false;
		break;
	case '2':
		obj2ani = true;
		obj1ani = false;
		break;
	case '3':
		obj1ani = true;
		obj2ani = true;
		break;
	case 'r':
		x1RotateAni = 30.0f;
		x2RotateAni = 30.0f;
		y1RotateAni = -30.0f;
		y2RotateAni = -30.0f;
		gong ? gong = false : gong = true;
		timer ? timer = false : timer = true;
		gongkey = 1;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'R':
		x1RotateAni = 30.0f;
		x2RotateAni = 30.0f;
		y1RotateAni = -30.0f;
		y2RotateAni = -30.0f;
		gong ? gong = false : gong = true;
		timer ? timer = false : timer = true;
		gongkey = 2;
		glutTimerFunc(10, Timer, 1);
		break;
	case 'c':
		obj ? obj = false : obj = true;
		Initvbovao();
		break;
	}
	glutPostRedisplay();
}
