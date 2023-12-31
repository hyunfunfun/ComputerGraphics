#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat vertex[8][3] = { 
		{-0.5,-0.5,0.0},{-0.5,0.5,0.0},
		{-0.5,0.5,0.0},{0.5,0.5,0.0},
		{0.5,0.5,0.0},{0.5,-0.5,0.0},
		{0.5,-0.5,0.0},{-0.5,-0.5,0.0}
	};
	GLfloat colors[8][3] = {
	{0.0,1.0,0.0}, {1.0,0.0,0.0},
	{1.0,0.0,0.0},{1.0,1.0,0.0},
	{1.0,1.0,0.0}, {0.0,0.0,1.0},
	{0.0,0.0,1.0}, {0.0,1.0,1.0} 
	};
	GLuint vao, vbo[2];
	GLuint ebo;
};

unsigned int index[] = {
		0,1,3,
		1,2,3
};
Shape shape;

int out_rec = 0;
bool in_rec = false;
float prevx = 0;
float prevy = 0;
GLfloat rColor=1, gColor=1, bColor=1;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void UpdateBuffer();
void Draw();

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	width = 800;
	height = 600;
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);

	glutCreateWindow("Drill10");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	/*초기화 함수*/
	make_shaderProgram();
	Initvbovao();

	/*콜백 함수*/
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}

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



GLvoid drawScene() {

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);
	/*vao vbo 자동 업데이트*/
	UpdateBuffer();
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
	glGenVertexArrays(1, &shape.vao);
	glGenBuffers(2, shape.vbo);

	glBindVertexArray(shape.vao);

	glBindBuffer(GL_ARRAY_BUFFER, shape.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape.vertex), shape.vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, shape.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape.colors), shape.colors, GL_STATIC_DRAW);
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glEnableVertexAttribArray(PosLocation);
	glEnableVertexAttribArray(ColorLocation);
	
}

void UpdateBuffer() {

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	glBindVertexArray(shape.vao);
	glEnableVertexAttribArray(PosLocation);
	glEnableVertexAttribArray(ColorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, shape.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape.vertex), shape.vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, shape.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape.colors), shape.colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glBindVertexArray(shape.vao);
	glLineWidth(5);
	
	glDrawArrays(GL_LINES, 0, 8);
	glDisableVertexAttribArray(PosLocation);
	glDisableVertexAttribArray(ColorLocation);
	
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

GLvoid Mouse(int button, int state, int x, int y) {
	float ox = (float)x / 400 - 1;
	float oy = -((float)y / 300 - 1);
	prevx = ox;
	prevy = oy;
	float range = 0.1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if ((ox >= shape.vertex[0][0] - range) && (ox <= shape.vertex[0][0] + range) && (oy >= shape.vertex[0][1] - range) && (oy <= shape.vertex[0][1] + range)) {
			out_rec = 1;
		}
		else if ((ox >= shape.vertex[2][0] - range) && (ox <= shape.vertex[2][0] + range) && (oy >= shape.vertex[2][1] - range) && (oy <= shape.vertex[2][1] + range)) {
			out_rec = 2;
		}
		else if ((ox >= shape.vertex[4][0] - range) && (ox <= shape.vertex[4][0] + range) && (oy >= shape.vertex[4][1] - range) && (oy <= shape.vertex[4][1] + range)) {
			out_rec = 3;
		}
		else if ((ox >= shape.vertex[6][0] - range) && (ox <= shape.vertex[6][0] + range) && (oy >= shape.vertex[6][1] - range) && (oy <= shape.vertex[6][1] + range)) {
			out_rec = 4;
		}
		else if ((ox > shape.vertex[0][0]) && (ox < shape.vertex[3][0]) && (oy > shape.vertex[0][1]) && (oy < shape.vertex[3][1])) {
			in_rec = true;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		out_rec = 0;
		in_rec = false;
	}
}


GLvoid Motion(int x, int y) {

	float ox = (float)x / 400 - 1;
	float oy = -((float)y / 300 - 1);
	
	if (out_rec == 1) {
		shape.vertex[0][0] = shape.vertex[7][0] = ox;
		shape.vertex[0][1] = shape.vertex[7][1] = oy;
	}
	else if (out_rec == 2) {
		shape.vertex[1][0] = shape.vertex[2][0] = ox;
		shape.vertex[1][1] = shape.vertex[2][1] = oy;
	}
	else if (out_rec == 3) {
		shape.vertex[3][0] = shape.vertex[4][0] = ox;
		shape.vertex[3][1] = shape.vertex[4][1] = oy;
	}
	else if (out_rec == 4) {
		shape.vertex[5][0] = shape.vertex[6][0] = ox;
		shape.vertex[5][1] = shape.vertex[6][1] = oy;
	}
	if (in_rec == true) {
		for (int i = 0; i < 8; i++) {
			shape.vertex[i][0] += (ox - prevx);
			shape.vertex[i][1] += (oy-prevy);
		}
		prevx = ox;
		prevy = oy;
	}
	glutPostRedisplay();
}