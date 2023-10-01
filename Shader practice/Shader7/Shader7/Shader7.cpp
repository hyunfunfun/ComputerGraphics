#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include "Header.h"

typedef struct Shape {
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;
	int check = false;
};
//--- 메인 함수
//--- 함수 선언 추가하기

Shape shape[10];

GLfloat triShape[3][3];
GLfloat tricolors[3][3] = { //--- 삼각형 꼭지점 색상
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };

GLfloat pointShape[3];//점 위치
GLfloat pointcolors[3] = { 0.0,1.0,0.0 };

GLfloat lineShape[2][3];
GLfloat linecolors[2][3]= {{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }};

GLfloat recShape[4][3];
GLfloat reccolors[4][3] = { //--- 삼각형 꼭지점 색상
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } ,{1.0,1.0,0.0} };
unsigned int index[] = { 0,1,3,1,2,3 };

int objcount = 0;

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void InitBuffer(int a);
char* filetobuf(const char*);

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	make_shaderProgram();
	//InitBuffer();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	//--- 사용할 VAO 불러오기
	for (int i = 0; i < objcount; i++) {
		if (shape[i].check == 3) {
			glBindVertexArray(shape[i].vao);
			//--- 삼각형 그리기
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else if (shape[i].check == 1) {
			glBindVertexArray(shape[i].vao);
			glPointSize(10);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		else if (shape[i].check == 2) {
			glBindVertexArray(shape[i].vao);
			glLineWidth(10);
			glDrawArrays(GL_LINES, 0, 2);
		}
		else if (shape[i].check == 4) {
			glBindVertexArray(shape[i].vao);
			//--- 삼각형 그리기
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	glutSwapBuffers(); //--- 화면에 출력하기
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void InitBuffer(int a)
{
	switch (a) {
	case 1://삼각형
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(shape[objcount].vao); //--- VAO를 바인드하기
		glGenBuffers(2, shape[objcount].vbo); //--- 2개의 VBO를 지정하고 할당하기
		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		//--- triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 0번을 사용가능하게 함
		glEnableVertexAttribArray(0);
		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- 변수 colors에서 버텍스 색상을 복사한다.
		//--- colors 배열의 사이즈: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), tricolors, GL_STATIC_DRAW);
		//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 1번을 사용 가능하게 함.
		glEnableVertexAttribArray(1);
		objcount++;
		break;
	case 2://점
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(shape[objcount].vao); //--- VAO를 바인드하기
		glGenBuffers(2, shape[objcount].vbo); //--- 2개의 VBO를 지정하고 할당하기
		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		//--- triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), pointShape, GL_STATIC_DRAW);
		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 0번을 사용가능하게 함
		glEnableVertexAttribArray(0);
		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- 변수 colors에서 버텍스 색상을 복사한다.
		//--- colors 배열의 사이즈: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), pointcolors, GL_STATIC_DRAW);
		//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 1번을 사용 가능하게 함.
		glEnableVertexAttribArray(1);
		objcount++;
	case 3://선
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(shape[objcount].vao); //--- VAO를 바인드하기
		glGenBuffers(2, shape[objcount].vbo); //--- 2개의 VBO를 지정하고 할당하기
		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		//--- triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), lineShape, GL_STATIC_DRAW);
		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 0번을 사용가능하게 함
		glEnableVertexAttribArray(0);
		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- 변수 colors에서 버텍스 색상을 복사한다.
		//--- colors 배열의 사이즈: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), linecolors, GL_STATIC_DRAW);
		//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute 인덱스 1번을 사용 가능하게 함.
		glEnableVertexAttribArray(1);
		objcount++;
	case 4://사각형
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(shape[objcount].vao); //--- VAO를 바인드하기
		glGenBuffers(2, shape[objcount].vbo); //--- 2개의 VBO를 지정하고 할당하기
		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장

		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		//--- triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), recShape, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
		glEnableVertexAttribArray(0);
		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- 변수 colors에서 버텍스 색상을 복사한다.
		//--- colors 배열의 사이즈: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), reccolors, GL_STATIC_DRAW);
		//--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//--- attribute 인덱스 1번을 사용 가능하게 함.
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &shape[objcount].ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[objcount].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(index), index, GL_STATIC_DRAW);
		objcount++;
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
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
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
		std::cout << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
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

void keyboard(unsigned char key, int x, int y) {
	float ogx = ((float)x / 400) - 1;
	float ogy = -(((float)y / 300) - 1);
	if (objcount < 10) {
		switch (key) {
		case 'p':
			shape[objcount].check = 1;
			pointShape[0] = ogx;
			pointShape[1] = ogy;
			InitBuffer(2);
			glutPostRedisplay();
			break;
		case 't':
			shape[objcount].check = 3;
			triShape[0][0] = ogx - 0.1;
			triShape[0][1] = ogy - 0.1;
			triShape[1][0] = ogx + 0.1;
			triShape[1][1] = ogy - 0.1;
			triShape[2][0] = ogx;
			triShape[2][1] = ogy + 0.1;
			InitBuffer(1);
			glutPostRedisplay();
			break;
		case 'l':
			shape[objcount].check = 2;
			lineShape[0][0] = ogx - 0.1;
			lineShape[0][1] = ogy;
			lineShape[1][0] = ogx + 0.1;
			lineShape[1][1] = ogy;
			InitBuffer(3);
			glutPostRedisplay();
			break;
		case 'r':
			shape[objcount].check = 4;
			recShape[0][0] = ogx - 0.1;
			recShape[0][1] = ogy - 0.1;
			recShape[1][0] = ogx + 0.1;
			recShape[1][1] = ogy - 0.1;
			recShape[2][0] = ogx + 0.1;
			recShape[2][1] = ogy + 0.1;
			recShape[3][0] = ogx - 0.1;
			recShape[3][1] = ogy + 0.1;
			InitBuffer(4);
			glutPostRedisplay();
			break;
		}
	}
}