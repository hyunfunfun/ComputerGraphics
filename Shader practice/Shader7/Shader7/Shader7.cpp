#define _CRT_SECURE_NO_WARNINGS //--- ���α׷� �� �տ� ������ ��
#include "Header.h"

typedef struct Shape {
	GLuint vao;
	GLuint vbo[2];
	GLuint ebo;
	int check = false;
};
//--- ���� �Լ�
//--- �Լ� ���� �߰��ϱ�

Shape shape[10];

GLfloat triShape[3][3];
GLfloat tricolors[3][3] = { //--- �ﰢ�� ������ ����
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };

GLfloat pointShape[3];//�� ��ġ
GLfloat pointcolors[3] = { 0.0,1.0,0.0 };

GLfloat lineShape[2][3];
GLfloat linecolors[2][3]= {{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }};

GLfloat recShape[4][3];
GLfloat reccolors[4][3] = { //--- �ﰢ�� ������ ����
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } ,{1.0,1.0,0.0} };
unsigned int index[] = { 0,1,3,1,2,3 };

int objcount = 0;

GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint shaderProgramID; //--- ���̴� ���α׷�

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void InitBuffer(int a);
char* filetobuf(const char*);

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
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
	//--- ����� ���� ����
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(shaderProgramID);
	//--- ����� VAO �ҷ�����
	for (int i = 0; i < objcount; i++) {
		if (shape[i].check == 3) {
			glBindVertexArray(shape[i].vao);
			//--- �ﰢ�� �׸���
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
			//--- �ﰢ�� �׸���
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}
//--- �ٽñ׸��� �ݹ� �Լ�
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void InitBuffer(int a)
{
	switch (a) {
	case 1://�ﰢ��
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(shape[objcount].vao); //--- VAO�� ���ε��ϱ�
		glGenBuffers(2, shape[objcount].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		//--- triShape �迭�� ������: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 0���� ��밡���ϰ� ��
		glEnableVertexAttribArray(0);
		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
		//--- colors �迭�� ������: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), tricolors, GL_STATIC_DRAW);
		//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 1���� ��� �����ϰ� ��.
		glEnableVertexAttribArray(1);
		objcount++;
		break;
	case 2://��
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(shape[objcount].vao); //--- VAO�� ���ε��ϱ�
		glGenBuffers(2, shape[objcount].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		//--- triShape �迭�� ������: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), pointShape, GL_STATIC_DRAW);
		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 0���� ��밡���ϰ� ��
		glEnableVertexAttribArray(0);
		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
		//--- colors �迭�� ������: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), pointcolors, GL_STATIC_DRAW);
		//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 1���� ��� �����ϰ� ��.
		glEnableVertexAttribArray(1);
		objcount++;
	case 3://��
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(shape[objcount].vao); //--- VAO�� ���ε��ϱ�
		glGenBuffers(2, shape[objcount].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		//--- triShape �迭�� ������: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), lineShape, GL_STATIC_DRAW);
		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 0���� ��밡���ϰ� ��
		glEnableVertexAttribArray(0);
		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
		//--- colors �迭�� ������: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), linecolors, GL_STATIC_DRAW);
		//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- attribute �ε��� 1���� ��� �����ϰ� ��.
		glEnableVertexAttribArray(1);
		objcount++;
	case 4://�簢��
		glGenVertexArrays(1, &shape[objcount].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(shape[objcount].vao); //--- VAO�� ���ε��ϱ�
		glGenBuffers(2, shape[objcount].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����

		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[0]);
		//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		//--- triShape �迭�� ������: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), recShape, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
		glEnableVertexAttribArray(0);
		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, shape[objcount].vbo[1]);
		//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
		//--- colors �迭�� ������: 9 *float 
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), reccolors, GL_STATIC_DRAW);
		//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//--- attribute �ε��� 1���� ��� �����ϰ� ��.
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &shape[objcount].ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape[objcount].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(index), index, GL_STATIC_DRAW);
		objcount++;
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
		std::cout << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
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
		std::cout << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
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