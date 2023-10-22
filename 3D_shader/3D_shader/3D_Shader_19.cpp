#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat spivertex[360][3] = { 0 };
	GLfloat spicolors[360][3] = { 0 };
	GLfloat colors[3000][3];
	GLuint vbo[2], vao, ebo;
};

Shape s[4];

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

//��ġ,ȸ��,����

double x1move = 0.0;
double y1move = 0.0;
double x2move = 0.5;
double y2move = 0.0;
double z1move = 0.0;
double z2move = 0.0;

float radius = 1.5f;

bool pcheck = false;
bool mcheck = false;
GLfloat rColor = 1, gColor = 1, bColor = 1;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL���� �Լ�*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

/*���̴� ���� �Լ�*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo ���� �Լ�*/
void Initvbovao();
void Draw();
void Drawspi();

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
	if (pcheck == false)
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	else if (pcheck == true) {
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	}
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	/*�׸���*/
	Draw();
	Drawspi();
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
	for (int i = 0; i < 3000; i++) {
		s[0].colors[i][0] = 0.2;
		s[0].colors[i][1] = 0.2;
		s[0].colors[i][2] = 1.0;
	}
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	
	Load_Object("sphere.obj");
	{
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);
		glGenBuffers(1, &s[0].ebo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[0].colors), s[0].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[0].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	{
		for (int i = 0; i < 360; i++)
		{
			s[1].spivertex[i][0] = cos(i / 100.0f * (2.0f * 3.141592)) * radius;  // x��ǥ
			s[1].spivertex[i][2] = sin(i / 100.0f * (2.0f * 3.141592)) * radius;   // y��ǥ
			s[1].spicolors[i][0] = 0.0f, s[0].spicolors[i][1] = 0.0f, s[0].spicolors[i][2] = 0.0f;
		}
		glGenVertexArrays(1, &s[1].vao);
		glGenBuffers(2, s[1].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[1].spivertex), s[1].spivertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(s[1].spicolors), s[1].spicolors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}
void Draw() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR = glm::translate(TR, glm::vec3(x1move, y1move, z1move)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

		glBindVertexArray(s[0].vao);
		if(mcheck==false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, 0);
	}
}

void Drawspi()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR1 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	glm::mat4 TR2 = glm::mat4(1.0f); //--- �ռ� ��ȯ ���

	{
		TR = glm::translate(TR, glm::vec3(x1move, y1move, z1move)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0)); //--- y�࿡ ���Ͽ� ȸ�� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

		glBindVertexArray(s[1].vao);
		glDrawArrays(GL_LINE_STRIP, 0, 360);
	}
	{
		TR1 = glm::translate(TR1, glm::vec3(x1move, y1move, z1move)); //--- x������ �̵� ���
		TR1 = glm::rotate(TR1, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR1 = glm::rotate(TR1, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0)); //--- x�࿡ ���Ͽ� ȸ�� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform ������ ��

		glBindVertexArray(s[1].vao);
		glDrawArrays(GL_LINE_STRIP, 0, 360);
	}
	{
		TR2 = glm::translate(TR2, glm::vec3(x1move, y1move, z1move)); //--- x������ �̵� ���
		TR2 = glm::rotate(TR2, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
		TR2 = glm::rotate(TR2, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0)); //--- x�࿡ ���Ͽ� ȸ�� ���

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform ������ ��

		glBindVertexArray(s[1].vao);
		glDrawArrays(GL_LINE_STRIP, 0, 360);
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
	case 'p':
		pcheck=true;
		break;
	case 'P':
		pcheck = false;
		break;
	case 'm':
		mcheck = true;
		break;
	case 'M':
		mcheck = false;
		break;
	}
	glutPostRedisplay();
}
