#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat colors[36][3];
	GLuint vbo[2], vao, ebo;
};

GLfloat vertex[][3] = {
	{1.0,0.,1.0},
	{1.0,0,-1.0},
	{-1.0,0,1.0},
	{-1.0,0,1.0},
	{1.0,0,-1.0},
	{-1.0,0,-1.0}
};
Shape s[7];

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

//위치,회전,신축

double xmove1 = 0.0;
double ymove1 = 0.0;
double zmove1 = 0.0;

double xmove2 = 0.2;
double ymove2 = 0.1;
double zmove2 = 0.4;

float xRotate1 = 0.0f;
float yRotate1 = 0.0f;
float zRotate1_1 = 0.0f;
float zRotate1_2 = 0.0f;

float xRotate2 = 0.0f;
float yRotate2_1 = 0.0f;
float yRotate2_2 = 0.0f;
float zRotate2 = 0.0f;

int mode = 1;

float yAngle = 1.0f;
float dis = 5.0f;
//timer
bool timer = true;
bool btimer = false;
bool Btimer = false;

bool mtimer = false;
bool Mtimer = false;

bool ftimer = false;
bool Ftimer = false;

bool etimer = false;
bool Etimer = false;

bool ttimer = false;
bool Ttimer = false;

bool atimer = false;
bool Atimer = false;
int value1 = 1;

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
void Initvbovao();
void Draw();
void Drawtank();

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
	glutTimerFunc(10, Timer, 1);
	glutMainLoop();

	return 0;
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 view = glm::mat4(1.0f);
	cameraPos.y = 3.0;
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	/*그리기*/
	Draw();
	Drawtank();

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	{
		for (int i = 0; i < 6; i++) {
			s[0].colors[i][0] = 1.0;
			s[0].colors[i][1] = 1.0;
			s[0].colors[i][2] = 1.0;
		}
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[0].colors), s[0].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	Load_Object("cube.obj");
	//아래몸체
	{
		for (int i = 0; i < 36; i++) {
			s[1].colors[i][0] = 0.2;
			s[1].colors[i][1] = 0.2;
			s[1].colors[i][2] = 1.0;
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
	//중앙몸체
	{
		for (int i = 0; i < 36; i++) {
			s[2].colors[i][0] = 0.3;
			s[2].colors[i][1] = 0.3;
			s[2].colors[i][2] = 0.8;
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
	{//위 팔
		for (int i = 0; i < 36; i++) {
			s[3].colors[i][0] = 0.8;
			s[3].colors[i][1] = 0.5;
			s[3].colors[i][2] = 0.2;
			s[4].colors[i][0] = 0.8;
			s[4].colors[i][1] = 0.5;
			s[4].colors[i][2] = 0.2;
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
	{//아래 포신
		for (int i = 0; i < 36; i++) {
			s[5].colors[i][0] = 0.2;
			s[5].colors[i][1] = 0.6;
			s[5].colors[i][2] = 0.2;
			s[6].colors[i][0] = 0.2;
			s[6].colors[i][1] = 0.6;
			s[6].colors[i][2] = 0.2;
		}
		glGenVertexArrays(1, &s[5].vao);
		glGenBuffers(2, s[5].vbo);
		glGenBuffers(1, &s[5].ebo);

		glBindVertexArray(s[5].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[5].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[5].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[5].colors), s[5].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[5].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);

		glGenVertexArrays(1, &s[6].vao);
		glGenBuffers(2, s[6].vbo);
		glGenBuffers(1, &s[6].ebo);

		glBindVertexArray(s[6].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[6].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[6].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[6].colors), s[6].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[6].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}
void Draw() {//바닥
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(0, -0.2, 0)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(2, 2, 2));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES,0,6);
	}
}

void Drawtank() {//탱크
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = glm::translate(TR, glm::vec3(xmove1, ymove1, zmove1)); //--- x축으로 이동 행렬
		TR = glm::scale(TR, glm::vec3(1.5, 1, 1.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[1].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	glm::mat4 TR2 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR2 = glm::translate(TR2, glm::vec3(xmove1, ymove1 + 0.4, zmove1)); //--- x축으로 이동 행렬
		TR2 = glm::rotate(TR2, glm::radians(xRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR2 = glm::rotate(TR2, glm::radians(yRotate1), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR2 = glm::scale(TR2, glm::vec3(1, 0.5, 1));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform 변수에 변

		glBindVertexArray(s[2].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glm::mat4 TR3 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR3 = glm::translate(TR3, glm::vec3(xmove1, ymove1, zmove1)); //--- x축으로 이동 행렬
		TR3 = glm::rotate(TR3, glm::radians(yRotate1), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR3 = glm::rotate(TR3, glm::radians(xRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR3 = glm::translate(TR3, glm::vec3(-0.2, 0.6, 0.0)); //--- x축으로 이동 행렬
		TR3 = glm::rotate(TR3, glm::radians(zRotate1_1), glm::vec3(0.0, 0.0, 1.0)); //--- y축에 대하여 회전 행렬
		TR3 = glm::scale(TR3, glm::vec3(0.3, 0.6, 0.3));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR3)); //--- modelTransform 변수에 변

		glBindVertexArray(s[3].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glm::mat4 TR4 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR4 = glm::translate(TR4, glm::vec3(xmove1, ymove1, zmove1)); //--- x축으로 이동 행렬
		TR4 = glm::rotate(TR4, glm::radians(yRotate1), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR4 = glm::rotate(TR4, glm::radians(xRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR4 = glm::translate(TR4, glm::vec3( 0.2, 0.6, 0.0)); //--- x축으로 이동 행렬
		TR4 = glm::rotate(TR4, glm::radians(zRotate1_2), glm::vec3(0.0, 0.0, 1.0)); //--- y축에 대하여 회전 행렬
		TR4 = glm::scale(TR4, glm::vec3(0.3, 0.6, 0.3));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR4)); //--- modelTransform 변수에 변

		glBindVertexArray(s[4].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glm::mat4 TR5 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR5 = glm::translate(TR5, glm::vec3(xmove1, ymove1, zmove1)); //--- x축으로 이동 행렬
		TR5 = glm::rotate(TR5, glm::radians(xRotate2), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR5 = glm::rotate(TR5, glm::radians(yRotate2_1), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR5 = glm::translate(TR5, glm::vec3(xmove2, ymove2, zmove2)); //--- x축으로 이동 행렬
		TR5 = glm::scale(TR5, glm::vec3(0.4, 0.4, 0.7));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR5)); //--- modelTransform 변수에 변

		glBindVertexArray(s[5].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glm::mat4 TR6 = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		TR6 = glm::translate(TR6, glm::vec3(xmove1, ymove1, zmove1)); //--- x축으로 이동 행렬
		TR6 = glm::rotate(TR6, glm::radians(xRotate2), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR6 = glm::rotate(TR6, glm::radians(yRotate2_2), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR6 = glm::translate(TR6, glm::vec3(-xmove2, ymove2, zmove2)); //--- x축으로 이동 행렬
		TR6 = glm::scale(TR6, glm::vec3(0.4, 0.4, 0.7));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR6)); //--- modelTransform 변수에 변

		glBindVertexArray(s[6].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	case 'b':
		btimer ? btimer = false : btimer = true;
		break;
	case 'B':
		Btimer ? Btimer = false : Btimer = true;
		break;
	case 'm':
		mtimer ? mtimer = false : mtimer = true;
		break;
	case 'M':
		Mtimer ? Mtimer = false : Mtimer = true;
		break;
	case 'f':
		ftimer ? ftimer = false : ftimer = true;
		break;
	case 'F':
		Ftimer ? Ftimer = false : Ftimer = true;
		break;
	case 'e':
		etimer ? etimer = false : etimer = true;
		break;
	case 'E':
		Etimer ? Etimer = false : Etimer = true;
		break;
	case 't':
		ttimer ? ttimer = false : ttimer = true;
		break;
	case 'T':
		Ttimer ? Ttimer = false : Ttimer = true;
		break;
	case 'z':
		cameraPos.z += 0.1;
		dis = cameraPos.z;
		break;
	case 'Z':
		cameraPos.z -= 0.1;
		break;
	case 'x':
		cameraPos.x += 0.1;
		break;
	case 'X':
		cameraPos.x -= 0.1;
		break;
	case 'y':
		yAngle += 0.1;
		cameraDirection.z = dis * cos(yAngle);
		cameraDirection.x = dis * sin(yAngle);
		break;
	case 'Y':
		yAngle -= 0.1;
		cameraDirection.z = dis * cos(yAngle);
		cameraDirection.x = dis * sin(yAngle);
		break;
	case 'r':
		cameraDirection.z = 0.0f;
		cameraDirection.x = 0.0f;
		yAngle += 0.1;
		cameraPos.z = dis * cos(yAngle);
		cameraPos.x = dis * sin(yAngle);
		break;
	case 'R':
		cameraDirection.z = 0.0f;
		cameraDirection.x = 0.0f;
		yAngle -= 0.1; 
		cameraPos.z = dis * cos(yAngle);
		cameraPos.x = dis * sin(yAngle);
		break;
	case 'a':
		atimer ? atimer = false : atimer = true;
		break;
	case 'A':
		Atimer ? Atimer = false : Atimer = true;
		break;
	case 's':
		timer = false;
		break;
	case 'S':
		timer = true;
		break;
	case 'c':
		xmove1 = 0.0;
		yRotate1 = 0.0f;
		yRotate2_1 = 0.0f;
		yRotate2_2 = 0.0f;
		xmove2 = 0.0;
		zRotate1_1 = 0.0;
		zRotate1_2 = 0.0;
		yAngle = 0;
		cameraPos.z = 5;
		cameraPos.x = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid Timer(int value) {
	if(timer==true)
	{
		if (btimer == true) {
			xmove1 += 0.01;
		}
		if (Btimer == true) {
			xmove1 -= 0.01;
		}
		if (mtimer == true) {
			yRotate1 += 1;
		}
		if (Mtimer == true) {
			yRotate1 -= 1;
		}
		if (ftimer == true) {
			if (yRotate2_1 > 360 || yRotate2_2 > 360) {
				yRotate2_1 = 0;
				yRotate2_2 = 0;
			}
			yRotate2_1 += 1;
			yRotate2_2 -= 1;
		}
		if (Ftimer == true) {
			if (yRotate2_1 > 360 || yRotate2_2 > 360) {
				yRotate2_1 = 0;
				yRotate2_2 = 0;
			}
			yRotate2_1 -= 1;
			yRotate2_2 += 1;
		}
		if (etimer == true) {
			if (yRotate2_1<10 && yRotate2_1>-10) {
				if (xmove2 > 0.0)
					xmove2 -= 0.01;
			}
			else {
				if (yRotate2_1 > yRotate2_2) {
					yRotate2_1 -= 1;
					yRotate2_2 += 1;
				}
				else {
					yRotate2_1 += 1;
					yRotate2_2 -= 1;
				}
			}
		}
		if (ttimer == true) {
			if (mode == 1) {
				zRotate1_1 += 1;
				zRotate1_2 -= 1;
				if (zRotate1_1 > 90) {
					mode = 2;
				}
			}
			else {
				zRotate1_1 -= 1;
				zRotate1_2 += 1;
				if (zRotate1_1 < -90) {
					mode = 1;
				}
			}
		}
		if (Ttimer == true) {
			if (mode == 1) {
				zRotate1_1 -= 1;
				zRotate1_2 += 1;
				if (zRotate1_1 < -90) {
					mode = 2;
				}
			}
			else {
				zRotate1_1 += 1;
				zRotate1_2 -= 1;
				if (zRotate1_1 > 90) {
					mode = 1;
				}
			}
		}
		if (atimer == true) {
			yAngle += 0.01;
			cameraPos.z = dis * cos(yAngle);
			cameraPos.x = dis * sin(yAngle);
		}
		if (Atimer == true) {
			yAngle -= 0.01;
			cameraPos.z = dis * cos(yAngle);
			cameraPos.x = dis * sin(yAngle);
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer, 1);
	}
}
