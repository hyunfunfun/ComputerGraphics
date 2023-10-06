#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat vertex[9][3] = { 0 };
	GLfloat colors[9][3] = { 0 };
	GLuint vao, vbo[2];
	int status;
	int presta;
};

Shape shape[4];

GLfloat point[3] = {
	0.0,0.0,0.0
};
GLfloat line[2][3] = {
	{-0.25,-0.25,0.0},
	{0.25,0.25,0.0},
};
GLfloat tri[3][3] = {
	{-0.25, -0.25, 0.0},
	{0.25, -0.25, 0.0},
	{0.0,0.25,0.0}
};
GLfloat rec[6][3] = {
	{-0.25, -0.25, 0.0},
	{0.25, -0.25, 0.0},
	{-0.25,0.25,0.0},

	{0.25, -0.25, 0.0},
	{-0.25,0.25,0.0},
	{0.25,0.25,0.0}
};
GLfloat penta[9][3] = {
	{-0.15,-0.25,0.0},
	{0.15,-0.25,0.0},
	{-0.3,0.0,0.0},

	{0.15,-0.25,0.0},
	{-0.3,0.0,0.0},
	{0.3,0.0,0.0},

	{-0.3,0.0, 0.0},
	{0.3, 0.0, 0.0},
	{0.0, 0.25,0.0}
};

GLfloat rColor=1, gColor=1, bColor=1;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void UpdateBuffer();
void Draw();
void Set();

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
	Set();
	Initvbovao();

	/*콜백 함수*/
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(10, TimerFunction, 1);
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
	for(int i=0;i<4;i++)
	{
		glGenVertexArrays(1, &shape[i].vao);
		glGenBuffers(2, shape[i].vbo);

		glBindVertexArray(shape[i].vao);
		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].vertex), shape[i].vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].colors), shape[i].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void UpdateBuffer() {

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	for(int i=0;i<4;i++)
	{
		glBindVertexArray(shape[i].vao);
		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].vertex), shape[i].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].colors), shape[i].colors, GL_STATIC_DRAW);
	}
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	for (int i = 0; i < 4; i++)
	{
		if (shape[i].status == 1)
		{
			glLineWidth(10);
			glBindVertexArray(shape[i].vao);
			glDrawArrays(GL_LINES, 0, 2);
		}
		if (shape[i].status == 2)
		{
			glBindVertexArray(shape[i].vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if (shape[i].status == 3)
		{
			glBindVertexArray(shape[i].vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (shape[i].status == 4)
		{
			glBindVertexArray(shape[i].vao);
			glDrawArrays(GL_TRIANGLES, 0, 9);
		}
		if (shape[i].status == 5)
		{
			glPointSize(10);
			glBindVertexArray(shape[i].vao);
			glDrawArrays(GL_POINTS, 0, 1);
		}


		glDisableVertexAttribArray(PosLocation);
		glDisableVertexAttribArray(ColorLocation);
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

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'l':
		
		break;
	}
}

void Set() {
	{
		shape[0].status = 1;
		shape[0].presta = 1;
		for (int i = 0; i < 2; i++) {
			shape[0].vertex[i][0] = line[i][0]-0.5;
			shape[0].vertex[i][1] = line[i][1] + 0.5;
		}
		shape[0].vertex[2][0] = line[1][0] - 0.5;
		shape[0].vertex[2][1] = line[1][1] + 0.5;
		for (int i = 0; i < 9; i++) {
			shape[0].colors[i][0] = 0.0, shape[0].colors[i][1] = 0.0, shape[0].colors[i][2] = 1.0;
		}
	}
	{
		shape[1].status = 2;
		shape[1].presta = 2;
		for (int i = 0; i < 3; i++) {
			shape[1].vertex[i][0] = tri[i][0] + 0.5;
			shape[1].vertex[i][1] = tri[i][1] + 0.5;
		}
		for (int i = 0; i < 9; i++) {
			shape[1].colors[i][0] = 1.0, shape[1].colors[i][1] = 1.0, shape[1].colors[i][2] = 0.0;
		}
	}
	{
		shape[2].status = 3;
		shape[2].presta = 3;
		for (int i = 0; i < 6; i++) {
			shape[2].vertex[i][0] = rec[i][0] - 0.5;
			shape[2].vertex[i][1] = rec[i][1] - 0.5;
		}
		for (int i = 0; i < 9; i++) {
			shape[2].colors[i][0] = 0.0, shape[2].colors[i][1] = 1.0, shape[2].colors[i][2] = 0.0;
		}
	}
	{
		shape[3].status = 4;
		shape[3].presta = 4;
		for (int i = 0; i < 9; i++) {
			shape[3].vertex[i][0] = penta[i][0] + 0.5;
			shape[3].vertex[i][1] = penta[i][1] - 0.5;
		}

		for (int i = 0; i < 9; i++) {
			shape[3].colors[i][0] = 1.0, shape[3].colors[i][1] = 0.0, shape[3].colors[i][2] = 0.0;
		}
	}
}

GLvoid TimerFunction(int value)
{
	float move = 0.001;
	/*상태 변화하는 함수를 넣어두는 용도로 많이 사용함*/

	if(shape[0].presta==1)//선-삼각
	{
		shape[0].status = 2;
		if (shape[0].vertex[2][0] > tri[2][0] - 0.5) {
			shape[0].vertex[2][0] -= move;
		}
		if (shape[0].vertex[1][1] > tri[1][1] + 0.5) {
			shape[0].vertex[1][1] -= move;
		}
		if ((shape[0].vertex[2][0] <= tri[2][0] - 0.5) && (shape[0].vertex[1][1] <= tri[1][1] + 0.5)) {
			shape[0].presta = 2;
			shape[0].vertex[5][0] = shape[0].vertex[2][0];
			shape[0].vertex[5][1] = shape[0].vertex[2][1];
		}
	}
	if (shape[0].presta == 2)//삼각-사각
	{
		shape[0].status = 3;
		shape[0].vertex[3][0] = shape[0].vertex[1][0];
		shape[0].vertex[3][1] = shape[0].vertex[1][1];
		shape[0].vertex[4][0] = shape[0].vertex[2][0];
		shape[0].vertex[4][1] = shape[0].vertex[2][1];
		if (shape[0].vertex[2][0] > rec[2][0] - 0.5) {
			shape[0].vertex[2][0] -= move;
		}
		if (shape[0].vertex[5][0] < rec[5][0]+0.5) {
			shape[0].vertex[5][0] += move;
		}
		if ((shape[0].vertex[2][0] <= rec[2][0] - 0.5) && (shape[0].vertex[5][1] >= rec[5][1] + 0.5)) {
			shape[0].presta = 3;
			shape[0].vertex[8][0] = shape[0].vertex[5][0];
			shape[0].vertex[8][1] = shape[0].vertex[5][1];
		}
	}
	if (shape[0].presta == 3)//사각-오각
	{
		shape[0].status = 4;
		shape[0].vertex[3][0] = shape[0].vertex[1][0];
		shape[0].vertex[3][1] = shape[0].vertex[1][1];
		shape[0].vertex[4][0] = shape[0].vertex[2][0];
		shape[0].vertex[4][1] = shape[0].vertex[2][1];
		shape[0].vertex[6][0] = shape[0].vertex[4][0];
		shape[0].vertex[6][1] = shape[0].vertex[4][1];
		shape[0].vertex[7][0] = shape[0].vertex[5][0];
		shape[0].vertex[7][1] = shape[0].vertex[5][1];
		if (shape[0].vertex[0][0] < penta[0][0] - 0.5) {
			shape[0].vertex[0][0] += move;
		}
		if (shape[0].vertex[1][0] > penta[1][0] - 0.5) {
			shape[0].vertex[1][0] -= move;
		}
		if (shape[0].vertex[2][0] > penta[2][0] - 0.5) {
			shape[0].vertex[2][0] -= move;
		}
		if (shape[0].vertex[2][1] > penta[2][1] + 0.5) {
			shape[0].vertex[2][1] -= move;
		}
		if (shape[0].vertex[5][0] < penta[5][0]-0.5) {
			shape[0].vertex[5][0] += move;
		}
		if (shape[0].vertex[5][1] > penta[5][1] + 0.5) {
			shape[0].vertex[5][1] -= move;
		}
		if (shape[0].vertex[8][0] > penta[8][0] - 0.5) {
			shape[0].vertex[8][0] -= move;
		}
		if ((shape[0].vertex[0][0] >= penta[0][0] - 0.5) && (shape[0].vertex[1][0] <= penta[1][0] - 0.5) && (shape[0].vertex[2][0] <= penta[2][0] - 0.5) &&
			(shape[0].vertex[2][1] <= penta[2][1] + 0.5) && (shape[0].vertex[5][0] >= penta[5][0] - 0.5) && (shape[0].vertex[5][1] <= penta[5][1] + 0.5) &&
			(shape[0].vertex[8][0] <= penta[8][0] - 0.5)) {
			shape[0].presta = 4;
		}
	}
	if (shape[0].presta == 4) {
		for (int i = 0; i < 9; i++) {
			if (shape[0].vertex[i][0] > point[0] - 0.5) {
				shape[0].vertex[i][0] -= move;
			}
			if (shape[0].vertex[i][0] < point[0] - 0.5) {
				shape[0].vertex[i][0] += move;
			}
			if (shape[0].vertex[i][1] > point[1] + 0.5) {
				shape[0].vertex[i][1] -= move;
			}					   
			if (shape[0].vertex[i][1] < point[1] + 0.5) {
				shape[0].vertex[i][1] += move;
			}
		}
		if ((shape[0].vertex[2][0] >= point[0] - 0.501) && (shape[0].vertex[5][0] <= point[0] - 0.491)) {
			std::cout << "1" << std::endl;
			shape[0].vertex[0][0] = point[0] - 0.5;
			shape[0].vertex[0][1] = point[1] + 0.5;
			shape[0].vertex[1][0] = shape[0].vertex[0][0];
			shape[0].vertex[1][1] = shape[0].vertex[0][1];
			shape[0].status = 5;
			shape[0].presta = 5;
		}
	}
	if (shape[0].presta == 5)//점-선
	{
		shape[0].status = 1;

		if (shape[0].vertex[0][0] > line[0][0] - 0.5) {
			shape[0].vertex[0][0] -= move;
		}
		if (shape[0].vertex[0][1] > line[0][1] + 0.5) {
			shape[0].vertex[0][1] -= move;
		}
		if (shape[0].vertex[1][0] < line[1][0] - 0.5) {
			shape[0].vertex[1][0] += move;
		}
		if (shape[0].vertex[1][1] < line[1][1] + 0.5) {
			shape[0].vertex[1][1] += move;
		}
		if ((shape[0].vertex[0][0] <= line[0][0] - 0.5) && (shape[0].vertex[0][1] <= line[0][1] + 0.5) &&
			(shape[0].vertex[1][0] >= line[1][0] - 0.5) && (shape[0].vertex[1][1] >= line[0][1] + 0.5)) {
			shape[0].vertex[2][0] = line[1][0] - 0.5;
			shape[0].vertex[2][1] = line[1][1] + 0.5;
			shape[0].presta = 1;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(3, TimerFunction, 1);
}