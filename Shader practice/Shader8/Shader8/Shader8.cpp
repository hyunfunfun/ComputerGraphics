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


void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	srand(time(NULL));
	width = 800;
	height = 600;
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
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

	//--- ����� ���� ����
	glClearColor(rColor, gColor, bColor, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(shaderProgramID);
	//--- ����� VAO �ҷ�����
	for (int i = 0; i < 4; i++) {
		glBindVertexArray(shape[i].vao);
		//--- �ﰢ�� �׸���
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void InitBuffer(int a)
{
	glGenVertexArrays(1, &shape[a].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(shape[a].vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, shape[a].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, shape[a].vbo[0]);
	//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	//--- triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), shape[a].triShape, GL_STATIC_DRAW);
	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);
	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, shape[a].vbo[1]);
	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//--- colors �迭�� ������: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), shape[a].colors, GL_STATIC_DRAW);
	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	glEnableVertexAttribArray(1);
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
		if (ogx < 0 && ogy>0) {//1��и�
			shape[0].triShape[0][0] = ogx - ransize;
			shape[0].triShape[0][1] = ogy - ransize;
			shape[0].triShape[1][0] = ogx + ransize;
			shape[0].triShape[1][1] = ogy - ransize;
			shape[0].triShape[2][0] = ogx;
			shape[0].triShape[2][1] = ogy + ransize+0.3;
			InitBuffer(0);
		}
		else if (ogx > 0 && ogy>0) {//2��и�
			shape[1].triShape[0][0] = ogx - ransize;
			shape[1].triShape[0][1] = ogy - ransize;
			shape[1].triShape[1][0] = ogx + ransize;
			shape[1].triShape[1][1] = ogy - ransize;
			shape[1].triShape[2][0] = ogx;
			shape[1].triShape[2][1] = ogy + ransize + 0.3;
			InitBuffer(1);
		}
		else if (ogx > 0 && ogy < 0) {//3��и�
			shape[2].triShape[0][0] = ogx - ransize;
			shape[2].triShape[0][1] = ogy - ransize;
			shape[2].triShape[1][0] = ogx + ransize;
			shape[2].triShape[1][1] = ogy - ransize;
			shape[2].triShape[2][0] = ogx;
			shape[2].triShape[2][1] = ogy + ransize + 0.3;
			InitBuffer(2);
		}
		else if (ogx < 0 && ogy < 0) {//4��и�
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