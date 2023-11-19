#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLuint vbo[2], vao, ebo;
};

Shape s[4];

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
	{ 0.0, 1.0, 0.0 }, //1
	{ 0.0, 1.0, 0.0 }, //2

	{ 0.0, 1.0, 0.0 }, //0
	{ 0.0, 1.0, 0.0 }, //2
	{ 0.0, 1.0, 0.0 }, //3

	{ 0.0, 1.0, 0.0 }, //4
	{ 0.0, 1.0, 0.0 }, //6
	{ 0.0, 1.0, 0.0 }, //5

	{ 0.0, 1.0, 0.0 }, //4
	{ 0.0, 1.0, 0.0 }, //7
	{ 0.0, 1.0, 0.0 }, //6

	{ 0.0, 1.0, 0.0 }, //0
	{ 0.0, 1.0, 0.0 }, //3
	{ 0.0, 1.0, 0.0 }, //4

	{ 0.0, 1.0, 0.0 }, //3
	{ 0.0, 1.0, 0.0 }, //7
	{ 0.0, 1.0, 0.0 }, //4

	{ 0.0, 1.0, 0.0 }, //1
	{ 0.0, 1.0, 0.0 }, //5
	{ 0.0, 1.0, 0.0 }, //2

	{ 0.0, 1.0, 0.0 }, //6
	{ 0.0, 1.0, 0.0 }, //2
	{ 0.0, 1.0, 0.0 }, //5

	{ 0.0, 1.0, 0.0 }, //1
	{ 0.0, 1.0, 0.0 }, //0
	{ 0.0, 1.0, 0.0 }, //4

	{ 0.0, 1.0, 0.0 }, //1
	{ 0.0, 1.0, 0.0 }, //4
	{ 0.0, 1.0, 0.0 }, //5

	{ 0.0, 1.0, 0.0 }, //2
	{ 0.0, 1.0, 0.0 }, //7
	{ 0.0, 1.0, 0.0 }, //3

	{ 0.0, 1.0, 0.0 }, //2
	{ 0.0, 1.0, 0.0 }, //6
	{ 0.0, 1.0, 0.0 }, //7


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
	 { 0.0, 1.0, 0.0 }, //0
	 { 0.0, 1.0, 0.0 },	//2
	 { 0.0, 1.0, 0.0 },	//1

	 { 0.0, 1.0, 0.0 },	//0
	 { 0.0, 1.0, 0.0 },	//3
	 { 0.0, 1.0, 0.0 },	//2

	 { 0.0, 1.0, 0.0 },	//1
	 { 0.0, 1.0, 0.0 },	//2
	 { 0.0, 1.0, 0.0 },	//4

	 { 0.0, 1.0, 0.0 },	//0
	 { 0.0, 1.0, 0.0 },	//4
	 { 0.0, 1.0, 0.0 },	//3

	 { 0.0, 1.0, 0.0 },	//0
	 { 0.0, 1.0, 0.0 },	//1
	 { 0.0, 1.0, 0.0 },	//4

	 { 0.0, 1.0, 0.0 },	//2
	 { 0.0, 1.0, 0.0 },	//3
	 { 0.0, 1.0, 0.0 },	//4
};

float vertices[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

bool mode = true;

bool timer = false;
int Key = 0;
float xRotateAni = 0.0f;
float yRotateAni = 0.0f;
double xMove = 0.0, yMove = 0.0, zMove = 0.0;

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;


GLfloat rColor = 0, gColor = 0, bColor = 0;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

glm::vec3 lightPosition(0.0f, 3.0f, 0.0f);

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
void Initbuffer();
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
	Initbuffer();
	glClearColor(1.0, 1.0, 1.0, 1.0);

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

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 20.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projection"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 view = glm::mat4(1.0f);
	cameraPos.y = 3.0;
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "view"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	/*그리기*/
	Draw();

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "vNormal");
	{
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	{
		glGenVertexArrays(1, &s[1].vao);
		glGenBuffers(2, s[1].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void Initbuffer() {

	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int NormalLocation = glGetAttribLocation(shaderProgramID, "vNormal");
	//조명
	{
		glGenVertexArrays(1, &s[2].vao);
		glGenBuffers(1, s[2].vbo);

		glBindVertexArray(s[2].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

		//glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[1]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(NormalLocation);

		glUseProgram(shaderProgramID);
		unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
		glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);
		unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
		glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
		unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");
		glUniform3f(objColorLocation, 1.0, 0.5, 0.3);
		unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
		glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

	}
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "vNormal");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "model"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR1 = glm::mat4(1.0f); //--- 합성 변환 행렬
	TR1 = glm::translate(TR1, glm::vec3(xMove, yMove, zMove)); //--- x축으로 이동 행렬
	TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR1 = glm::rotate(TR1, glm::radians(30.0f + yRotateAni), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변

	if (mode == false) {
		glBindVertexArray(s[0].vao);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	if (mode == true) {
		glBindVertexArray(s[1].vao);

		glDrawArrays(GL_TRIANGLES, 0, 18);
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
	vertexSource = filetobuf("vertex1.glsl");
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
	fragmentSource = filetobuf("fragment1.glsl");
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
	if (timer == true)
	{
		glutPostRedisplay(); // 화면 재 출력
		yRotateAni += 0.5f;
		glutTimerFunc(10, Timer, 1);
	}
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'm':
		mode ? mode = false : mode = true;
		break;
	case 'y':
		timer ? timer = false : timer = true;
		glutTimerFunc(10, Timer, 1);
		break;
	}
	glutPostRedisplay();
}