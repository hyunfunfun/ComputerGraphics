#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat vertex[360 * 3][3] = { 0 };
	GLfloat colors[360 * 3][3] = { 0 };
	GLuint vao, vbo[2];
};

Shape shape;
int count = 1;
int countsum;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

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
	srand(time(NULL));
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
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1, TimerFunction, 1);
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
	GLfloat rColor, gColor, bColor;
	rColor = bColor = gColor = 0.0;

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
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0,0);

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
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glBindVertexArray(shape.vao);

	glPointSize(2);

	if (count < 360 * 3)
	{

			glDrawArrays(GL_POINTS, 0+count, count+ 2);

		count+=10;
		
	}
	else
		glDrawArrays(GL_POINTS, 0, count);
	
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

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {

	}
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		count = 0;
		GLfloat radius = 0.001f;
		GLfloat opglPosX = (GLfloat)x / 400 - 1;
		GLfloat opglposY = -((GLfloat)y / 300 - 1);

		for (int i = 0; i < 360 * 3; i++)
		{
			shape.vertex[i][0] = opglPosX + cos(i / 360.0f * (2.0f * 3.141592)) * radius;  // x좌표
			shape.vertex[i][1] = opglposY + sin(i / 360.0f * (2.0f * 3.141592)) * radius;   // y좌표
			shape.colors[i][0] = 1.0f, shape.colors[i][1] = 0.0f, shape.colors[i][2] = 0.0f;
			radius += 0.0003f;

		}
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	/*상태 변화하는 함수를 넣어두는 용도로 많이 사용함*/
	

	glutTimerFunc(100, TimerFunction, 1);
	glutPostRedisplay();
}