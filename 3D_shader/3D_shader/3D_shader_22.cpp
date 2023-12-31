#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat colors[36][3];
	GLuint vbo[2], vao, ebo;
};

Shape s[7];

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향


glm::vec3 ran1 = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 ran2= glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 ran3= glm::vec3(0.0f, 0.0f, 0.0f);
//위치,회전,신축

float yAngle = 0.0f;
float dis = 2.0f;
float doorRotate = 0.0f;

float chRotate = 0.0;
int Rotatemode = 0;
float chRotate1 = 0.0;

double movespeed = 0.02;
float moveangle = 45.0;
double xch = 0.0f;
double ych = 0.0f;
double zch = 0.0f;
double jump = 0.0f;
float jumpch = 0.0f;
int jumpmode = 0;
int walkmode = 0;

GLfloat vertex[][3] = {
	{ -1.0, 1.0, -1.0 }, //0
	{ 1.0, 1.0, -1.0 },//3
	{ -1.0, 1.0, 1.0 }, //1

	{ -1.0, 1.0, 1.0 }, //1
	{ 1.0, 1.0, -1.0 },//3
	{ 1.0, 1.0, 1.0 }, //2

	{ -1.0, -1.0, -1.0 },//4
	{ -1.0, -1.0, 1.0 },//5
	{ 1.0, -1.0, 1.0 },//6

	{ -1.0, -1.0, -1.0 },//4
	{ 1.0, -1.0, 1.0 },//6
	{ 1.0, -1.0, -1.0 },//7

	{ -1.0, 1.0, -1.0 }, //0
	{ -1.0, 1.0, 1.0 }, //1
	{ -1.0, -1.0, 1.0 },//5

	{ -1.0, 1.0, -1.0 }, //0
	{ -1.0, -1.0, 1.0 },//5
	{ -1.0, -1.0, -1.0 },//4

	{ 1.0, 1.0, 1.0 }, //2
	{ 1.0, 1.0, -1.0 },//3
	{ 1.0, -1.0, 1.0 },//6

	{ 1.0, 1.0, -1.0 },//3
	{ 1.0, -1.0, -1.0 },//7
	{ 1.0, -1.0, 1.0 },//6

	{ 1.0, 1.0, -1.0 },//3
	{ -1.0, 1.0, -1.0 }, //0
	{ -1.0, -1.0, -1.0 },//4

	{ 1.0, 1.0, -1.0 },//3
	{ -1.0, -1.0, -1.0 },//4
	{ 1.0, -1.0, -1.0 },//7

	{ 0.1, 1.0, 1.0 },//8
	{ -1.0, 1.0, 1.0 }, //1
	{ -1.0, -1.0, 1.0 },//5

	{ 0.1, 1.0, 1.0 },//8
	{ -1.0, -1.0, 1.0 },//5
	{ 0.1, -1.0, 1.0 },//10

	{ 1.0, 1.0, 1.0 }, //2
	{ 0.0, 1.0, 1.0 },//9
	{ 1.0, -1.0, 1.0 },//6

	{ 1.0, -1.0, 1.0 },//6
	{ 0.0, 1.0, 1.0 },//9
	{ 0.0, -1.0, 1.0 },//11
};
GLfloat colors[][3] = {

	{ 0.3, 0.6, 0.6 }, //0
	{ 0.3, 0.6, 0.6  },//3
	{ 0.3, 0.6, 0.6  }, //1

	{ 0.3, 0.6, 0.6  }, //1
	{ 0.3, 0.6, 0.6  },//3
	{ 0.3, 0.6, 0.6  }, //2

	{ 1.0, 1.0, 1.0 },//4
	{ 1.0, 1.0, 1.0 },//5
	{ 1.0, 1.0, 1.0 },//6

	{ 1.0, 1.0, 1.0 },//4
	{ 1.0, 1.0, 1.0 },//6
	{ 1.0, 1.0, 1.0 },//7

	{ 0.5, 0.1, 0.1 }, //0
	{ 0.5, 0.1, 0.1 }, //1
	{ 0.5, 0.1, 0.1 },//5

	{ 0.5, 0.1, 0.1 }, //0
	{ 0.5, 0.1, 0.1 },//5
	{ 0.5, 0.1, 0.1 },//4

	{ 1.0, 1.0, 0.0 }, //2
	{ 1.0, 1.0, 0.0 },//3
	{ 1.0, 1.0, 0.0 },//6

	{ 1.0, 1.0, 0.0 },//3
	{ 1.0, 1.0, 0.0 },//7
	{ 1.0, 1.0, 0.0 },//6

	{ 0.5, 0.5, 0.5 },//3
	{ 0.5, 0.5, 0.5 }, //0
	{ 0.5, 0.5, 0.5 },//4

	{ 0.5, 0.5, 0.5 },//3
	{ 0.5, 0.5, 0.5 },//4
	{ 0.5, 0.5, 0.5 },//7

	{  1.0, 0.1, 0.1 },//8
	{ 1.0, 0.1, 0.1}, //1
	{  1.0, 0.1, 0.1 },//5

	{ 1.0, 0.1, 0.1 },//8
	{  1.0, 0.1, 0.1 },//5
	{ 1.0, 0.1, 0.1 },//10

	{ 1.0, 0.1, 0.1 }, //2
	{ 1.0, 0.1, 0.1 },//9
	{  1.0, 0.1, 0.1 },//6

	{ 1.0, 0.1, 0.1 },//6
	{ 1.0, 0.1, 0.1 },//9
	{ 1.0, 0.1, 0.1 },//11
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
GLvoid keyup(unsigned char key, int x, int y);
GLvoid Timer(int value);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void Draw();
void Drawobj();
void Drawch();

//timer
bool timer = true;
bool doortimer = false;
bool jumptimer = false;

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
	glutKeyboardUpFunc(keyup);
	glutTimerFunc(10, Timer, 1);
	glutMainLoop();

	return 0;
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- 뷰잉 변환 설정
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -1.0));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	Draw();
	Drawobj();
	Drawch();

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
	{
		ran1.x = ((rand() % 21) * 0.1 - 1);
		ran1.y = -0.9f;
		ran1.z = ((rand() % 21) * 0.1 - 1);

		ran2.x = ((rand() % 21) * 0.1 - 1);
		ran2.y = -0.9f;
		ran2.z = ((rand() % 21) * 0.1 - 1);

		ran3.x = ((rand() % 21) * 0.1 - 1);
		ran3.y = -0.9f;
		ran3.z = ((rand() % 21) * 0.1 - 1);
	}
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	{
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);
		//glGenBuffers(1, &s[0].ebo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[0].ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	Load_Object("cube.obj");
	{
		for (int i = 0; i < 36; i++) {
			s[1].colors[i][0] = 0.5;
			s[1].colors[i][1] = 1.0;
			s[1].colors[i][2] = 0.5;
		}
		glGenVertexArrays(1, &s[1].vao);
		glGenBuffers(2, s[1].vbo);
		glGenBuffers(1, &s[1].ebo);

		glBindVertexArray(s[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[1].colors), s[1].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[1].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	{
		for (int i = 0; i < 36; i++) {
			s[2].colors[i][0] = 0.0;
			s[2].colors[i][1] = 0.0;
			s[2].colors[i][2] = 1.0;
		}
		glGenVertexArrays(1, &s[2].vao);
		glGenBuffers(2, s[2].vbo);
		glGenBuffers(1, &s[2].ebo);

		glBindVertexArray(s[2].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[2].colors), s[2].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[2].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	{
		for (int i = 0; i < 36; i++) {
			s[3].colors[i][0] = 0.0;
			s[3].colors[i][1] = 1.0;
			s[3].colors[i][2] = 0.0;
		}
		glGenVertexArrays(1, &s[3].vao);
		glGenBuffers(2, s[3].vbo);
		glGenBuffers(1, &s[3].ebo);

		glBindVertexArray(s[3].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[3].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[3].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[3].colors), s[3].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[3].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	{
		for (int i = 0; i < 36; i++) {
			s[4].colors[i][0] = 1.0;
			s[4].colors[i][1] = 0.0;
			s[4].colors[i][2] = 0.0;
		}
		glGenVertexArrays(1, &s[4].vao);
		glGenBuffers(2, s[4].vbo);
		glGenBuffers(1, &s[4].ebo);

		glBindVertexArray(s[4].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[4].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[4].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[4].colors), s[4].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[4].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}
void Draw() {//무대
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR1 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR2 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, 0, 0)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 0, 30);
	}
	{
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR1 = glm::translate(TR1, glm::vec3(-1, 0, 1)); //--- x축으로 이동 행렬
		TR1 = glm::rotate(TR1, glm::radians(-doorRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR1 = glm::translate(TR1, glm::vec3(1, 0, -1)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}
	{
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR2 = glm::translate(TR2, glm::vec3(1, 0, 1)); //--- x축으로 이동 행렬
		TR2 = glm::rotate(TR2, glm::radians(doorRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR2 = glm::translate(TR2, glm::vec3(-1, 0, -1)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform 변수에 변

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 36, 6);
	}
}
void Drawobj() {//장애물
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR1 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR2 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, ran1); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(0.5, 0.3, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[1].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT,0);
	}
	{
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR1 = glm::translate(TR1, ran2); //--- x축으로 이동 행렬
		TR1 = glm::scale(TR1, glm::vec3(0.5, 0.3, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변

		glBindVertexArray(s[1].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR2 = glm::translate(TR2, ran3); //--- x축으로 이동 행렬
		TR2 = glm::scale(TR2, glm::vec3(0.5, 0.3, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform 변수에 변

		glBindVertexArray(s[1].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void Drawch() {//캐릭터
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR1 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR2 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR3 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR4 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR5 = glm::mat4(1.0f); //--- 합성 변환 행렬
	glm::mat4 TR6 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{//머리
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(xch, ych-0.5+jump, zch)); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::scale(TR, glm::vec3(0.2, 0.2, 0.2)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[2].vao);
		glDrawElements(GL_TRIANGLES, 36,GL_UNSIGNED_INT, 0);
	}
	{//코
		TR6 = glm::rotate(TR6, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR6 = glm::translate(TR6, glm::vec3(xch, ych + jump, zch)); //--- x축으로 이동 행렬
		TR6 = glm::rotate(TR6, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR6 = glm::translate(TR6, glm::vec3(0.0, -0.5, -0.05)); //--- x축으로 이동 행렬
		TR6 = glm::scale(TR6, glm::vec3(0.05, 0.05, 0.05)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR6)); //--- modelTransform 변수에 변

		glBindVertexArray(s[3].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//몸통
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR1 = glm::translate(TR1, glm::vec3(xch, ych - 0.7 + jump, zch)); //--- x축으로 이동 행렬
		TR1 = glm::rotate(TR1, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR1 = glm::scale(TR1, glm::vec3(0.3, 0.5, 0.3)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변

		glBindVertexArray(s[2].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//오른팔
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR2 = glm::translate(TR2, glm::vec3(xch, ych, zch)); //--- x축으로 이동 행렬
		TR2 = glm::rotate(TR2, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR2 = glm::translate(TR2, glm::vec3(0.1, - 0.7 + jump, 0)); //--- x축으로 이동 행렬
		TR2 = glm::translate(TR2, glm::vec3(0, 0.1, 0));
		TR2 = glm::rotate(TR2, glm::radians(-chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR2 = glm::translate(TR2, glm::vec3(0, -0.1, 0));
		TR2 = glm::scale(TR2, glm::vec3(0.05, 0.3, 0.05)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform 변수에 변

		glBindVertexArray(s[3].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//오른다리
		TR3 = glm::rotate(TR3, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR3 = glm::translate(TR3, glm::vec3(xch, ych, zch)); //--- x축으로 이동 행렬
		TR3 = glm::rotate(TR3, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR3 = glm::translate(TR3, glm::vec3(0.03, -0.9 + jump, 0)); //--- x축으로 이동 행렬
		TR3 = glm::translate(TR3, glm::vec3(0, 0.1, 0));
		TR3 = glm::rotate(TR3, glm::radians(-chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR3 = glm::translate(TR3, glm::vec3(0, -0.1, 0));
		TR3 = glm::scale(TR3, glm::vec3(0.05, 0.3, 0.05)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR3)); //--- modelTransform 변수에 변

		glBindVertexArray(s[3].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//오른팔
		TR4 = glm::rotate(TR4, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR4 = glm::translate(TR4, glm::vec3(xch, ych, zch)); //--- x축으로 이동 행렬
		TR4 = glm::rotate(TR4, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR4 = glm::translate(TR4, glm::vec3(-0.1, -0.7 + jump, 0)); //--- x축으로 이동 행렬
		TR4 = glm::translate(TR4, glm::vec3(0, 0.1, 0));
		TR4 = glm::rotate(TR4, glm::radians(chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR4 = glm::translate(TR4, glm::vec3(0, -0.1, 0));
		TR4 = glm::scale(TR4, glm::vec3(0.05, 0.3, 0.05)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR4)); //--- modelTransform 변수에 변

		glBindVertexArray(s[4].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//오른다리
		TR5 = glm::translate(TR5, glm::vec3(xch, ych, zch)); //--- x축으로 이동 행렬
		TR5 = glm::rotate(TR5, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR5 = glm::translate(TR5, glm::vec3(-0.03, -0.9 + jump, 0)); //--- x축으로 이동 행렬
		TR5 = glm::translate(TR5, glm::vec3(0, 0.1, 0));
		TR5 = glm::rotate(TR5, glm::radians(chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR5 = glm::translate(TR5, glm::vec3(0, -0.1, 0));
		TR5 = glm::scale(TR5, glm::vec3(0.05, 0.3, 0.05)); //--- x축으로 이동 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR5)); //--- modelTransform 변수에 변

		glBindVertexArray(s[4].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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
	case 'o':
		doortimer = true;
		break;
	case 'z':
		cameraPos.z += 0.1;
		break;
	case 'Z':
		cameraPos.z -= 0.1;
		break;
	case 'x':
		cameraDirection.x += 0.1;
		cameraPos.x += 0.1;
		break;
	case 'X':
		cameraDirection.x -= 0.1;
		cameraPos.x -= 0.1;
		break;
	case 'y':
		cameraDirection.z = 0.0f;
		cameraDirection.x = 0.0f;
		yAngle += 0.1;
		cameraPos.z = dis * cos(yAngle);
		cameraPos.x = dis * sin(yAngle);
		break;
	case 'Y':
		cameraDirection.z = 0.0f;
		cameraDirection.x = 0.0f;
		yAngle -= 0.1;
		cameraPos.z = dis * cos(yAngle);
		cameraPos.x = dis * sin(yAngle);
		break;
	case 'w':
		if (walkmode == 0) {
			chRotate = 0;
			zch -= movespeed;
			if (zch < -1) {
				walkmode = 1;
			}
			if (jumpch == 0.0){
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		else if (walkmode == 1) {
			chRotate = 180;
			zch += movespeed;
			if (zch > 1) {
				walkmode = 0;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		break;
	case 's':
		if (walkmode == 0) {
			chRotate = 180;
			zch += movespeed;
			if (zch > 1) {
				walkmode = 1;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		else if (walkmode == 1) {
			chRotate = 0;
			zch -= movespeed;
			if (zch < -1) {
				walkmode = 0;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		break;
	case 'a':
		if (walkmode == 0) {
			chRotate = 90;
			xch -= movespeed;
			if (xch < -1) {
				walkmode = 1;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		else if (walkmode == 1) {
			chRotate = 270;
			xch += movespeed;
			if (xch > 1) {
				walkmode = 0;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		break;
	case 'd':
		if (walkmode == 0) {
			chRotate = 270;
			xch += movespeed;
			if (xch > 1) {
				walkmode = 1;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		else if (walkmode == 1) {
			chRotate = 90;
			xch -= movespeed;
			if (xch < -1) {
				walkmode = 0;
			}
			if (jumpch == 0.0) {
				if (ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15)
				{
					walkmode = 2;
				}
				if (ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)
				{
					walkmode = 2;
				}
			}
		}
		break;
	case '+':
		movespeed += 0.001;
		moveangle += 1;
		break;
	case '-':
		if(movespeed>0)
		{
			movespeed -= 0.001;
			moveangle -= 1;
		}
		break;
	case 'i':
		zch = 0;
		xch = 0;
		movespeed = 0.02;
		moveangle = 45.0;
		break;
	case 'j':
		jump = 0.0;
		jumpmode = 0;
		jumptimer = true;
		break;
	}
	glutPostRedisplay();
}

GLvoid keyup(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		walkmode = 0;
		break;
	case 's':
		walkmode = 0;
		break;
	case 'a':
		walkmode = 0;
		break;
	case 'd':
		walkmode = 0;
		break;
	}
}

GLvoid Timer(int value) {
	if (timer == true) {
		if (Rotatemode == 0) {
			if (chRotate1 < moveangle) {
				chRotate1 += 1;
			}
			else
				Rotatemode = 1;
		}
		else if (Rotatemode == 1) {
			if (chRotate1 > -moveangle) {
				chRotate1 -= 1;
			}
			else
				Rotatemode = 0;
		}
		if (doortimer == true) {
			if (doorRotate<180) {
				doorRotate += 1;
			}
		}
		if (jumptimer == true) {
			if ((ran1.z - 0.15 < zch && ran1.z + 0.15 > zch && xch > ran1.x - 0.15 && xch < ran1.x + 0.15) ||
				(ran2.z - 0.15 < zch && ran2.z + 0.15 > zch && xch > ran2.x - 0.15 && xch < ran2.x + 0.15) ||
				(ran3.z - 0.15 < zch && ran3.z + 0.15 > zch && xch > ran3.x - 0.15 && xch < ran3.x + 0.15)) {
				jumpch = 0.2;
			}
			else {
				jumpch = 0.0;
			}
			
			if (jumpmode == 0) {
				if (jump < 0.5) {
					jump += 0.01;
				}
				else
					jumpmode = 1;
			}
			else if (jumpmode == 1) {
				if (jump > jumpch) {
					jump -= 0.01;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
