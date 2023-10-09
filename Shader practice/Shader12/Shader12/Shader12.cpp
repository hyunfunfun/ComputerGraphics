#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat vertex[6][3];
	GLfloat colors[6][3] = {0};
	GLuint vao, vbo[2];
	GLuint ebo;
	int vercount;
};


Shape shape[15];

int select = -1;
int touch = -1;
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
GLvoid Set();

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void UpdateBuffer();
void Draw();


GLfloat point[3] = {
	0.0,0.0,0.0
};
GLfloat line[2][3] = {
	{-0.05,-0.05,0.0},
	{0.05,0.05,0.0},
};
GLfloat tri[3][3] = {
	{-0.05, -0.05, 0.0},
	{0.05, -0.05, 0.0},
	{0.0,0.05,0.0}
};
GLfloat rec[4][3] = {
	{-0.05, -0.05, 0.0},
	{0.05, -0.05, 0.0},
	{-0.05,0.05,0.0},
	{0.05,0.05,0.0}
};
GLfloat penta[5][3] = {
	{-0.025,-0.05,0.0},
	{0.025,-0.05,0.0},
	{-0.05,0.0,0.0},
	{0.05,0.0,0.0},
	{0.0, 0.05,0.0}
};

GLfloat hexa[6][3] = {
	{0.0,-0.05,0.0},
	{0.05,-0.025,0.0},
	{-0.05,-0.025,0.0},
	{-0.05,0.025,0.0},
	{0.05,0.025,0.0},
	{0.0,0.05,0.0}
};
unsigned int recindex[] = {
		0,1,2,
		1,2,3
};
unsigned int penindex[] = {
		0,1,2,
		2,1,3,
		2,3,4
};
unsigned int hexindex[] = {
		0,1,2,
		1,3,2,
		3,1,4,
		3,4,5
};
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
	Set();
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
	for(int i=0;i<15;i++)
	{
		glGenVertexArrays(1, &shape[i].vao);
		glGenBuffers(2, shape[i].vbo);
		glGenBuffers(1, &shape[i].ebo);

		glBindVertexArray(shape[i].vao);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].vertex), shape[i].vertex, GL_STATIC_DRAW);

		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


		if (shape[i].vercount == 3) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[i].ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(recindex), recindex, GL_STATIC_DRAW);
		}
		else if (shape[i].vercount == 4) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[i].ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(penindex), penindex, GL_STATIC_DRAW);
		}
		else if (shape[i].vercount == 5) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[i].ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexindex), hexindex, GL_STATIC_DRAW);
		}

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
	for(int i=0;i<15;i++)
	{
		glBindVertexArray(shape[i].vao);
		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].vertex), shape[i].vertex, GL_STATIC_DRAW);

		if (shape[i].vercount == 3) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[i].ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(recindex), recindex, GL_STATIC_DRAW);
		}
		else if (shape[i].vercount == 4) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[i].ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(penindex), penindex, GL_STATIC_DRAW);
		}
		else if (shape[i].vercount == 5) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[i].ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexindex), hexindex, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].colors), shape[i].colors, GL_STATIC_DRAW);
	}
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	for (int i = 0; i < 15; i++) {
		glBindVertexArray(shape[i].vao);
		if (shape[i].vercount == 0) {
			glPointSize(10);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		if (shape[i].vercount == 1) {
			glLineWidth(5);
			glDrawArrays(GL_LINES, 0, 2);
		}
		if (shape[i].vercount == 2) {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if (shape[i].vercount == 3) {
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		if (shape[i].vercount == 4) {
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		}
		if (shape[i].vercount == 5) {
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		}

	}

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

GLvoid Set() {
	float x = -0.9;
	float y = -0.9;
	int obcount = -1;
	for (int i = 0; i < 15; i++) {
		if (i % 3 == 0) {
			obcount++;
		}
		shape[i].vercount = obcount;
	}
	for (int i = 0; i < 15; i++) {
		if (shape[i].vercount==0) {
			shape[i].vertex[0][0] = point[0]+x;
			shape[i].vertex[0][1] = point[1]+y;
			for (int j = 0; j < 6; j++) {
				shape[i].colors[j][0] = 0.0, shape[i].colors[j][1] = 1.0, shape[i].colors[j][2] = 0.0;
			}
		}
		if (shape[i].vercount == 1) {
			for (int j = 0; j < 2; j++) {
				shape[i].vertex[j][0] = line[j][0] + x;
				shape[i].vertex[j][1] = line[j][1] + y;
			}
			for (int j = 0; j < 6; j++) {
				shape[i].colors[j][0] = 1.0, shape[i].colors[j][1] = 0.0, shape[i].colors[j][2] = 0.0;
			}
		}
		if (shape[i].vercount == 2) {
			for (int j = 0; j < 3; j++) {
				shape[i].vertex[j][0] = tri[j][0]+x;
				shape[i].vertex[j][1] = tri[j][1]+y;
			}
			for (int j = 0; j < 6; j++) {
				shape[i].colors[j][0] = 1.0, shape[i].colors[j][1] = 0.0, shape[i].colors[j][2] = 1.0;
			}
		}
		if (shape[i].vercount == 3) {
			for (int j = 0; j < 4; j++) {
				shape[i].vertex[j][0] = rec[j][0] + x;
				shape[i].vertex[j][1] = rec[j][1]+y;
			}
			for (int j = 0; j < 6; j++) {
				shape[i].colors[j][0] = 0.0, shape[i].colors[j][1] = 1.0, shape[i].colors[j][2] = 1.0;
			}
		}
		if (shape[i].vercount == 4) {
			for (int j = 0; j < 5; j++) {
				shape[i].vertex[j][0] = penta[j][0]+x;
				shape[i].vertex[j][1] = penta[j][1]+y;
			}
			for (int j = 0; j < 6; j++) {
				shape[i].colors[j][0] = 1.0, shape[i].colors[j][1] = 1.0, shape[i].colors[j][2] = 0.0;
			}
		}
		if (shape[i].vercount == 5) {
			for (int j = 0; j < 6; j++) {
				shape[i].vertex[j][0] = hexa[j][0] + x;
				shape[i].vertex[j][1] = hexa[j][1] + y;
			}
			for (int j = 0; j < 6; j++) {
				shape[i].colors[j][0] = 0.0, shape[i].colors[j][1] = 0.0, shape[i].colors[j][2] = 1.0;
			}
		}
		if (x < 0.7) {
			x += 0.4;
		}
		else {
			y += 0.5;
			x = -0.9;
		}
	}
}

GLvoid Mouse(int button, int state, int x, int y) {
	float ox = (float)x / 400 - 1;
	float oy = -((float)y / 300 - 1);
	prevx = ox;
	prevy = oy;
	for (int i = 0; i < 15; i++) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN
			&& ox > shape[i].vertex[0][0] && ox<shape[i].vertex[0][0] + 0.1 && oy>shape[i].vertex[0][1] && oy < shape[i].vertex[0][1] + 0.1) {
			select = i;
			break;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		select = -1;
	}
	
}


GLvoid Motion(int x, int y) {

	float ox = (float)x / 400 - 1;
	float oy = -((float)y / 300 - 1);
	float range = 0.1;

	for (int i = 0; i < 6; i++) {
		shape[select].vertex[i][0] += (ox - prevx);
		shape[select].vertex[i][1] += (oy - prevy);
	}
	prevx = ox;
	prevy = oy;
	
	glutPostRedisplay();
}