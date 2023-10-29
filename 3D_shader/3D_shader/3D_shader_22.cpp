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

double xdoor1 = 0.0f;
double xdoor2 = 0.0f;

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


bool timer = false;

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
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "viewTransform"); //--- ���� ��ȯ ����
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- ���� ��ȯ �� ����

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	Draw();

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

	//Load_Object("cube.obj");
	
}
void Draw() {//�ڽ�
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
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::translate(TR1, glm::vec3(xdoor1, 0, 0)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform ������ ��

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 30, 6);
	}
	{
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::translate(TR2, glm::vec3(xdoor2, 0, 0)); //--- x������ �̵� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform ������ ��

		glBindVertexArray(s[0].vao);
		glDrawArrays(GL_TRIANGLES, 36, 6);
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
		timer = true;
		break;
	}
	glutPostRedisplay();
}

GLvoid Timer(int value) {
	if (timer == true) {
		if (xdoor2 < 1) {
			xdoor1 -= 0.01;
			xdoor2 += 0.01;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}
