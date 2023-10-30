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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f); //--- ī�޶� ��ġ
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

//��ġ,ȸ��,����

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

/*OPGL���� �Լ�*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid Timer(int value);

/*���̴� ���� �Լ�*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo ���� �Լ�*/
void Initvbovao();
void Draw();
void Drawobj();
void Drawch();

//timer
bool timer = true;
bool doortimer = false;

char* filetobuf(const char* file)
{
	ifstream in(file, ios_base::binary);

	if (!in) {
		cerr << file << "���� ��ã��";
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
		cerr << path << "���� ��ã��";
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

	/*�ʱ�ȭ �Լ�*/
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
	//glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- ���� ��ȯ ����
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- ���� ��ȯ �� ����

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -1.0));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	Draw();
	Drawobj();
	Drawch();

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
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
void Draw() {//����
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR1 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR2 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0, 0, 0)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 0, 30);
	}
	{
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::translate(TR1, glm::vec3(-1, 0, 1)); //--- x������ �̵� ���
		TR1 = glm::rotate(TR1, glm::radians(-doorRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::translate(TR1, glm::vec3(1, 0, -1)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform ������ ��

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}
	{
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(1, 0, 1)); //--- x������ �̵� ���
		TR2 = glm::rotate(TR2, glm::radians(doorRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(-1, 0, -1)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform ������ ��

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 36, 6);
	}
}
void Drawobj() {//��ֹ�
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR1 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR2 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(0, -0.9, 0)); //--- x������ �̵� ���
		TR = glm::scale(TR, glm::vec3(0.5, 0.3, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

		glBindVertexArray(s[1].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT,0);
	}
	{
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::translate(TR1, glm::vec3(0.5, -0.9, 0.5)); //--- x������ �̵� ���
		TR1 = glm::scale(TR1, glm::vec3(0.5, 0.3, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform ������ ��

		glBindVertexArray(s[1].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(-0.5, -0.9, 0.3)); //--- x������ �̵� ���
		TR2 = glm::scale(TR2, glm::vec3(0.5, 0.3, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform ������ ��

		glBindVertexArray(s[1].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void Drawch() {//ĳ����
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR1 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR2 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR3 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR4 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR5 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR6 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{//�Ӹ�
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(xch, ych-0.5, zch)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::scale(TR, glm::vec3(0.2, 0.2, 0.2)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

		glBindVertexArray(s[2].vao);
		glDrawElements(GL_TRIANGLES, 36,GL_UNSIGNED_INT, 0);
	}
	{//��
		TR6 = glm::rotate(TR6, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR6 = glm::translate(TR6, glm::vec3(xch, ych, zch)); //--- x������ �̵� ���
		TR6 = glm::rotate(TR6, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR6 = glm::translate(TR6, glm::vec3(0.0, -0.5, -0.05)); //--- x������ �̵� ���
		TR6 = glm::scale(TR6, glm::vec3(0.05, 0.05, 0.05)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR6)); //--- modelTransform ������ ��

		glBindVertexArray(s[3].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//����
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::translate(TR1, glm::vec3(xch, ych - 0.7, zch)); //--- x������ �̵� ���
		TR1 = glm::rotate(TR1, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::scale(TR1, glm::vec3(0.3, 0.5, 0.3)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform ������ ��

		glBindVertexArray(s[2].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//������
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(xch, ych, zch)); //--- x������ �̵� ���
		TR2 = glm::rotate(TR2, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(0.1, - 0.7, 0)); //--- x������ �̵� ���
		TR2 = glm::translate(TR2, glm::vec3(0, 0.1, 0));
		TR2 = glm::rotate(TR2, glm::radians(-chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(0, -0.1, 0));
		TR2 = glm::scale(TR2, glm::vec3(0.05, 0.3, 0.05)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform ������ ��

		glBindVertexArray(s[3].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//�����ٸ�
		TR3 = glm::rotate(TR3, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR3 = glm::translate(TR3, glm::vec3(xch, ych, zch)); //--- x������ �̵� ���
		TR3 = glm::rotate(TR3, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR3 = glm::translate(TR3, glm::vec3(0.03, -0.9, 0)); //--- x������ �̵� ���
		TR3 = glm::translate(TR3, glm::vec3(0, 0.1, 0));
		TR3 = glm::rotate(TR3, glm::radians(-chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR3 = glm::translate(TR3, glm::vec3(0, -0.1, 0));
		TR3 = glm::scale(TR3, glm::vec3(0.05, 0.3, 0.05)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR3)); //--- modelTransform ������ ��

		glBindVertexArray(s[3].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//������
		TR4 = glm::rotate(TR4, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR4 = glm::translate(TR4, glm::vec3(xch, ych, zch)); //--- x������ �̵� ���
		TR4 = glm::rotate(TR4, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR4 = glm::translate(TR4, glm::vec3(-0.1, -0.7, 0)); //--- x������ �̵� ���
		TR4 = glm::translate(TR4, glm::vec3(0, 0.1, 0));
		TR4 = glm::rotate(TR4, glm::radians(chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR4 = glm::translate(TR4, glm::vec3(0, -0.1, 0));
		TR4 = glm::scale(TR4, glm::vec3(0.05, 0.3, 0.05)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR4)); //--- modelTransform ������ ��

		glBindVertexArray(s[4].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	{//�����ٸ�
		TR5 = glm::translate(TR5, glm::vec3(xch, ych, zch)); //--- x������ �̵� ���
		TR5 = glm::rotate(TR5, glm::radians(chRotate), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR5 = glm::translate(TR5, glm::vec3(-0.03, -0.9, 0)); //--- x������ �̵� ���
		TR5 = glm::translate(TR5, glm::vec3(0, 0.1, 0));
		TR5 = glm::rotate(TR5, glm::radians(chRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR5 = glm::translate(TR5, glm::vec3(0, -0.1, 0));
		TR5 = glm::scale(TR5, glm::vec3(0.05, 0.3, 0.05)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR5)); //--- modelTransform ������ ��

		glBindVertexArray(s[4].vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
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
		chRotate = 0;
		zch -= movespeed;
		break;
	case 's':
		chRotate = 180;
		zch += movespeed;
		break;
	case 'a':
		chRotate = 90;
		xch -= movespeed;
		break;
	case 'd':
		chRotate = 270;
		xch += movespeed;
		break;
	case '+':
		movespeed += 0.001;
		moveangle += 1;
		break;
	case '-':
		movespeed -= 0.001;
		moveangle -= 1;
		break;
	case 'i':
		zch = 0;
		xch = 0;
		movespeed = 0.02;
		moveangle = 45.0;
		break;
	}
	glutPostRedisplay();
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
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
