#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat colors[36][3];
	GLuint vbo[2], vao, ebo;
};

Shape s[9];

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;


glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 5.0f); //--- ī�޶� ��ġ
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

int lightmode = 0;
glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, -5.0f);

//��ġ,ȸ��,����

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

bool turnlight = false;

float yAngle = 1.0f;
float dis = 5.0f;
//timer
bool timer = false;

GLfloat rColor = 0.5, gColor = 0.5, bColor = 0.5;

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
void light();
void Draw();
void Drawtank();

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
bool ReadObj(const char* path) {
	temp_vertices.clear();
	temp_uvs.clear();
	temp_normals.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();
	vertexIndices.clear();
	normalIndices.clear();
	uvIndices.clear();
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("���� ��� Ȯ��\n");
		getchar();
		return false;
	}
	while (1) {
		char lineHeader[500];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("����");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			uvIndices.push_back(uvIndex[0]);
			normalIndices.push_back(normalIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			uvIndices.push_back(uvIndex[1]);
			normalIndices.push_back(normalIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			char sbuffer[1000];
			fgets(sbuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);

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
	light();

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
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projection"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "view"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	/*�׸���*/
	Draw();
	Drawtank();

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
void light() {
	glUseProgram(shaderProgramID);
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}
void Initvbovao()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int NormalLocation = glGetAttribLocation(shaderProgramID, "vNormal");
	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");
	{
		ReadObj("cube.obj");
		{
			glGenVertexArrays(1, &s[8].vao);
			glGenBuffers(2, s[8].vbo);

			glBindVertexArray(s[8].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[8].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[8].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
		ReadObj("cube.obj");
		{
			glGenVertexArrays(1, &s[0].vao);
			glGenBuffers(2, s[0].vbo);

			glBindVertexArray(s[0].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
		ReadObj("cube.obj");
		{//�Ʒ���ü
			glGenVertexArrays(1, &s[1].vao);
			glGenBuffers(2, s[1].vbo);

			glBindVertexArray(s[1].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
		ReadObj("cube.obj");
		{//�߾Ӹ�ü
			glGenVertexArrays(1, &s[2].vao);
			glGenBuffers(2, s[2].vbo);

			glBindVertexArray(s[2].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
		ReadObj("cube.obj");
		{//����
			glGenVertexArrays(1, &s[3].vao);
			glGenBuffers(2, s[3].vbo);

			glBindVertexArray(s[3].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[3].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[3].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);

			glGenVertexArrays(1, &s[4].vao);
			glGenBuffers(2, s[4].vbo);

			glBindVertexArray(s[4].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[4].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[4].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
		ReadObj("cube.obj");
		{//�Ʒ� ����
			glGenVertexArrays(1, &s[5].vao);
			glGenBuffers(2, s[5].vbo);

			glBindVertexArray(s[5].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[5].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[5].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);

			glGenVertexArrays(1, &s[6].vao);
			glGenBuffers(2, s[6].vbo);

			glBindVertexArray(s[6].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[6].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[6].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glUniform3f(objColorLocation, 0.2, 0.6, 0.2);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
		ReadObj("cube.obj");
		{//����
			glGenVertexArrays(1, &s[7].vao);
			glGenBuffers(2, s[7].vbo);

			glBindVertexArray(s[7].vao);

			glBindBuffer(GL_ARRAY_BUFFER, s[7].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, s[7].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(NormalLocation);
		}
	}
}

void Draw() {//����
	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int NormalLocation = glGetAttribLocation(shaderProgramID, "vNormal");

	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "model"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(lightPos.x, lightPos.y, lightPos.z)); //--- x������ �̵� ���
		TR = glm::scale(TR, glm::vec3(0.5, 0.5, 0.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glBindVertexArray(s[7].vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glm::mat4 TR1 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::translate(TR1, glm::vec3(0, -0.5, 0)); //--- x������ �̵� ���
		TR1 = glm::scale(TR1, glm::vec3(10, 0.5, 10));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform ������ ��
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glBindVertexArray(s[8].vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Drawtank() {//��ũ
	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int NormalLocation = glGetAttribLocation(shaderProgramID, "vNormal");

	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "model");
	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR = glm::translate(TR, glm::vec3(xmove1, ymove1, zmove1)); //--- x������ �̵� ���
		TR = glm::scale(TR, glm::vec3(1.5, 1, 1.5));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��
		glUniform3f(objColorLocation, 1.0, 1.0, 1.0);
		glBindVertexArray(s[1].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glm::mat4 TR2 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR2 = glm::translate(TR2, glm::vec3(xmove1, ymove1 + 0.4, zmove1)); //--- x������ �̵� ���
		TR2 = glm::rotate(TR2, glm::radians(xRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::rotate(TR2, glm::radians(yRotate1), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::scale(TR2, glm::vec3(1, 0.5, 1));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform ������ ��

		glUniform3f(objColorLocation, 0.2, 0.2, 1.0);
		glBindVertexArray(s[2].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glm::mat4 TR3 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR3 = glm::translate(TR3, glm::vec3(xmove1, ymove1, zmove1)); //--- x������ �̵� ���
		TR3 = glm::rotate(TR3, glm::radians(yRotate1), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR3 = glm::rotate(TR3, glm::radians(xRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR3 = glm::translate(TR3, glm::vec3(-0.2, 0.6, 0.0)); //--- x������ �̵� ���
		TR3 = glm::rotate(TR3, glm::radians(zRotate1_1), glm::vec3(0.0, 0.0, 1.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR3 = glm::scale(TR3, glm::vec3(0.3, 0.6, 0.3));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR3)); //--- modelTransform ������ ��

		glUniform3f(objColorLocation, 0.3, 0.3, 0.8);

		glBindVertexArray(s[3].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glm::mat4 TR4 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR4 = glm::translate(TR4, glm::vec3(xmove1, ymove1, zmove1)); //--- x������ �̵� ���
		TR4 = glm::rotate(TR4, glm::radians(yRotate1), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR4 = glm::rotate(TR4, glm::radians(xRotate1), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR4 = glm::translate(TR4, glm::vec3(0.2, 0.6, 0.0)); //--- x������ �̵� ���
		TR4 = glm::rotate(TR4, glm::radians(zRotate1_2), glm::vec3(0.0, 0.0, 1.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR4 = glm::scale(TR4, glm::vec3(0.3, 0.6, 0.3));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR4)); //--- modelTransform ������ ��

		glUniform3f(objColorLocation, 0.8, 0.5, 0.2);
		glBindVertexArray(s[4].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glm::mat4 TR5 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR5 = glm::translate(TR5, glm::vec3(xmove1, ymove1, zmove1)); //--- x������ �̵� ���
		TR5 = glm::rotate(TR5, glm::radians(xRotate2), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR5 = glm::rotate(TR5, glm::radians(yRotate2_1), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR5 = glm::translate(TR5, glm::vec3(xmove2, ymove2, zmove2)); //--- x������ �̵� ���
		TR5 = glm::scale(TR5, glm::vec3(0.4, 0.4, 0.7));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR5)); //--- modelTransform ������ ��

		glUniform3f(objColorLocation, 0.8, 0.5, 0.2);
		glBindVertexArray(s[5].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glm::mat4 TR6 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR6 = glm::translate(TR6, glm::vec3(xmove1, ymove1, zmove1)); //--- x������ �̵� ���
		TR6 = glm::rotate(TR6, glm::radians(xRotate2), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR6 = glm::rotate(TR6, glm::radians(yRotate2_2), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR6 = glm::translate(TR6, glm::vec3(-xmove2, ymove2, zmove2)); //--- x������ �̵� ���
		TR6 = glm::scale(TR6, glm::vec3(0.4, 0.4, 0.7));

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR6)); //--- modelTransform ������ ��

		glUniform3f(objColorLocation, 0.2, 0.6, 0.2);

		glBindVertexArray(s[6].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
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
	vertexSource = filetobuf("vertex1.glsl");
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
	fragmentSource = filetobuf("fragment1.glsl");
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
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	switch (key) {
	
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
		timer = true;
		break;
	case 's':
		timer = false;
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
	case 'c':
		lightmode++;
		switch (lightmode) {
		case 1:
			glUniform3f(lightColorLocation, 0.1, 0.5, 1.0);
			break;
		case 2:
			glUniform3f(lightColorLocation, 0.5, 0.8, 0.6);
			break;
		case 3:
			glUniform3f(lightColorLocation, 0.8, 0.3, 0.4);
			break;
		default:
			lightmode = 0;
		}
		break;
	case 'm':
		turnlight ? turnlight = false : turnlight = true;
		if (turnlight==true)
			glUniform3f(lightColorLocation, 0, 0, 0);
		else if (turnlight==false)
			glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid Timer(int value) {
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	if (timer == true) {
		yAngle += 0.01;
		lightPos.x = dis * sin(yAngle);
		lightPos.z = dis * cos(yAngle);
		glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
