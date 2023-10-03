#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat triShape[3][3];
	GLfloat colors[3][3];
	GLuint vao, vbo[2];
};
Shape shape[4];

void set();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
void InitBuffer(int a);
void Mouse(int button, int state, int x, int y);

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

int objcount = 0;

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
	
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	make_shaderProgram();
	set();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene() {
	GLfloat rColor, gColor, bColor;
	rColor = bColor = gColor = 1.0;

	//--- 변경된 배경색 설정
	glClearColor(rColor, gColor, bColor, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	//--- 사용할 VAO 불러오기
	for (int i = 0; i < 4; i++) {
		glBindVertexArray(shape[i].vao);
		//--- 삼각형 그리기
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glutSwapBuffers(); //--- 화면에 출력하기
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void InitBuffer(int a)
{
	glGenVertexArrays(1, &shape[a].vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(shape[a].vao); //--- VAO를 바인드하기
	glGenBuffers(2, shape[a].vbo); //--- 2개의 VBO를 지정하고 할당하기
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, shape[a].vbo[0]);
	//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	//--- triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), shape[a].triShape, GL_STATIC_DRAW);
	//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);
	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, shape[a].vbo[1]);
	//--- 변수 colors에서 버텍스 색상을 복사한다.
	//--- colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), shape[a].colors, GL_STATIC_DRAW);
	//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);
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

void set() {
	float loca = 0.5;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			shape[i].triShape[0][0] = -loca - 0.1;
			shape[i].triShape[0][1] = loca;
			shape[i].triShape[1][0] = -loca + 0.1;
			shape[i].triShape[1][1] = loca;
			shape[i].triShape[2][0] = -loca;
			shape[i].triShape[2][1] = loca + 0.3;
			for (int j = 0; j < 4; j++) {
				shape[i].colors[j][0] = 1.0;
				shape[i].colors[j][1] = 0.0;
				shape[i].colors[j][2] = 0.0;
			}
			objcount++;
			InitBuffer(i);
			break;
		case 1:
			shape[i].triShape[0][0] = loca - 0.1;
			shape[i].triShape[0][1] = loca;
			shape[i].triShape[1][0] = loca + 0.1;
			shape[i].triShape[1][1] = loca;
			shape[i].triShape[2][0] = loca;
			shape[i].triShape[2][1] = loca + 0.3;
			for (int j = 0; j < 4; j++) {
				shape[i].colors[j][0] = 0.0;
				shape[i].colors[j][1] = 1.0;
				shape[i].colors[j][2] = 0.0;
			}
			objcount++;
			InitBuffer(i);
			break;
		case 2:
			shape[i].triShape[0][0] = loca - 0.1;
			shape[i].triShape[0][1] = -loca;
			shape[i].triShape[1][0] = loca + 0.1;
			shape[i].triShape[1][1] = -loca;
			shape[i].triShape[2][0] = loca;
			shape[i].triShape[2][1] = -loca + 0.3;
			for (int j = 0; j < 4; j++) {
				shape[i].colors[j][0] = 0.0;
				shape[i].colors[j][1] = 0.0;
				shape[i].colors[j][2] = 1.0;
			}
			objcount++;
			InitBuffer(i);
			break;
		case 3:
			shape[i].triShape[0][0] = -loca - 0.1;
			shape[i].triShape[0][1] = -loca;
			shape[i].triShape[1][0] = -loca + 0.1;
			shape[i].triShape[1][1] = -loca;
			shape[i].triShape[2][0] = -loca;
			shape[i].triShape[2][1] = -loca + 0.3;
			for (int j = 0; j < 4; j++) {
				shape[i].colors[j][0] = 0.0;
				shape[i].colors[j][1] = 1.0;
				shape[i].colors[j][2] = 1.0;
			}
			objcount++;
			InitBuffer(i);
			break;
		}
	}
}
void Mouse(int button, int state, int x, int y) {
	float ogx = ((float)x / (width / 2)) - 1;
	float ogy = -(((float)y / (height / 2)) - 1);
	float ransize = ((float)((rand() % 3)+1) / 10.0);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (ogx < 0 && ogy>0) {//1사분면
			shape[0].triShape[0][0] = ogx - ransize;
			shape[0].triShape[0][1] = ogy - ransize;
			shape[0].triShape[1][0] = ogx + ransize;
			shape[0].triShape[1][1] = ogy - ransize;
			shape[0].triShape[2][0] = ogx;
			shape[0].triShape[2][1] = ogy + ransize+0.3;
			InitBuffer(0);
		}
		else if (ogx > 0 && ogy>0) {//2사분면
			shape[1].triShape[0][0] = ogx - ransize;
			shape[1].triShape[0][1] = ogy - ransize;
			shape[1].triShape[1][0] = ogx + ransize;
			shape[1].triShape[1][1] = ogy - ransize;
			shape[1].triShape[2][0] = ogx;
			shape[1].triShape[2][1] = ogy + ransize + 0.3;
			InitBuffer(1);
		}
		else if (ogx > 0 && ogy < 0) {//3사분면
			shape[2].triShape[0][0] = ogx - ransize;
			shape[2].triShape[0][1] = ogy - ransize;
			shape[2].triShape[1][0] = ogx + ransize;
			shape[2].triShape[1][1] = ogy - ransize;
			shape[2].triShape[2][0] = ogx;
			shape[2].triShape[2][1] = ogy + ransize + 0.3;
			InitBuffer(2);
		}
		else if (ogx < 0 && ogy < 0) {//4사분면
			shape[3].triShape[0][0] = ogx - ransize;
			shape[3].triShape[0][1] = ogy - ransize;
			shape[3].triShape[1][0] = ogx + ransize;
			shape[3].triShape[1][1] = ogy - ransize;
			shape[3].triShape[2][0] = ogx;
			shape[3].triShape[2][1] = ogy + ransize + 0.3;
			InitBuffer(3);
		}
	}
}