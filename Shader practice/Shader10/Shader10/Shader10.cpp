#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLfloat vertex[360][3] = { 0 };
	GLfloat colors[360][3] = { 0 };
	GLuint vao, vbo[2];
};

Shape shape[5];
int count = 1;
bool pcheck = true;
bool lcheck = true;

int drawcount = 1;
GLfloat rColor=0, gColor=0, bColor=0;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL���� �Լ�*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

/*���̴� ���� �Լ�*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo ���� �Լ�*/
void Initvbovao();
void UpdateBuffer();
void Draw();

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

	glutCreateWindow("Drill10");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();

	/*�ʱ�ȭ �Լ�*/
	make_shaderProgram();
	Initvbovao();

	/*�ݹ� �Լ�*/
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutMainLoop();
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



GLvoid drawScene() {

	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgramID);
	/*vao vbo �ڵ� ������Ʈ*/
	UpdateBuffer();
	/*�׸���*/
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
	for(int i=0;i<5;i++)
	{
		glGenVertexArrays(1, &shape[i].vao);
		glGenBuffers(2, shape[i].vbo);

		glBindVertexArray(shape[i].vao);
		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].vertex), shape[i].vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].colors), shape[i].colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void UpdateBuffer() {

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	for(int i=0;i<5;i++)
	{
		glBindVertexArray(shape[i].vao);
		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].vertex), shape[i].vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, shape[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(shape[i].colors), shape[i].colors, GL_STATIC_DRAW);
	}
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");


	if (drawcount == 1) {
		glBindVertexArray(shape[0].vao);

		glPointSize(2);

		if (pcheck == true)
		{
			if (count < 360) {
				glDrawArrays(GL_POINTS, 0, count);
				++count;
			}

			if (count >= 360) {
				glDrawArrays(GL_POINTS, 0, 360);
			}
		}
		else if (lcheck == true) {
			if (count < 360) {
				glDrawArrays(GL_LINE_STRIP, 0, count);
				++count;
			}

			if (count >= 360) {
				glDrawArrays(GL_LINE_STRIP, 0, 360);
			}
		}

		glDisableVertexAttribArray(PosLocation);
		glDisableVertexAttribArray(ColorLocation);
	}
	else
	{
		for (int i = 0; i < drawcount; i++)
		{
			glBindVertexArray(shape[i].vao);

			glPointSize(2);

			if (pcheck == true)
			{
				if (count < 360) {
					glDrawArrays(GL_POINTS, 0, count);
					++count;
				}

				if (count >= 360) {
					glDrawArrays(GL_POINTS, 0, 360);
				}
			}
			else if (lcheck == true) {
				if (count < 360) {
					glDrawArrays(GL_LINE_STRIP, 0, count);
					++count;
				}

				if (count >= 360) {
					glDrawArrays(GL_LINE_STRIP, 0, 360);
				}
			}

			glDisableVertexAttribArray(PosLocation);
			glDisableVertexAttribArray(ColorLocation);
		}
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
		pcheck = true;
		lcheck = !lcheck;
		break;
	case 'l':
		lcheck = true;
		pcheck = !pcheck;
		break;
	case '1':
		drawcount = 1;
		break;
	case '2':
		drawcount = 2;
		break;
	case '3':
		drawcount = 3;
		break;
	case '4':
		drawcount = 4;
		break;
	case '5':
		drawcount = 5;
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		count = 0;
		GLfloat radius = 0.001f;
		GLfloat opglPosX = (GLfloat)x / 400 - 1;
		GLfloat opglPosY = -((GLfloat)y / 300 - 1);
		rColor = (rand() % 10) * 0.1;
		gColor = (rand() % 10) * 0.1;
		bColor = (rand() % 10) * 0.1;
		if(drawcount==1)
		{
			for (int i = 0; i < 180; i++)
			{
				shape[0].vertex[i][0] = opglPosX + cos(i / 60.0f * (2.0f * 3.141592)) * radius;  // x��ǥ
				shape[0].vertex[i][1] = opglPosY + sin(i / 60.0f * (2.0f * 3.141592)) * radius;   // y��ǥ
				shape[0].colors[i][0] = 1.0f, shape[0].colors[i][1] = 1.0f, shape[0].colors[i][2] = 1.0f;
				radius += 0.001f;
			}
			opglPosX += 0.36;
			for (int i = 180; i < 360; i++)
			{
				shape[0].vertex[i][0] = opglPosX + -(cos(i / 60.0f * (2.0f * 3.141592)) * radius);  // x��ǥ
				shape[0].vertex[i][1] = opglPosY + sin(i / 60.0f * (2.0f * 3.141592)) * radius;   // y��ǥ
				shape[0].colors[i][0] = 1.0f, shape[0].colors[i][1] = 1.0f, shape[0].colors[i][2] = 1.0f;
				radius -= 0.001f;
			}
		}
		else {
			for(int j=0;j<drawcount;j++)
			{
				opglPosX = ((rand() % 200) * 0.01)-1;
				opglPosY = ((rand() % 200) * 0.01)-1;
				for (int i = 0; i < 180; i++)
				{
					shape[j].vertex[i][0] = opglPosX + cos(i / 60.0f * (2.0f * 3.141592)) * radius;  // x��ǥ
					shape[j].vertex[i][1] = opglPosY + sin(i / 60.0f * (2.0f * 3.141592)) * radius;   // y��ǥ
					shape[j].colors[i][0] = 1.0f, shape[j].colors[i][1] = 1.0f, shape[j].colors[i][2] = 1.0f;
					radius += 0.001f;
				}
				opglPosX += 0.36;
				for (int i = 180; i < 360; i++)
				{
					shape[j].vertex[i][0] = opglPosX + -(cos(i / 60.0f * (2.0f * 3.141592)) * radius);  // x��ǥ
					shape[j].vertex[i][1] = opglPosY + sin(i / 60.0f * (2.0f * 3.141592)) * radius;   // y��ǥ
					shape[j].colors[i][0] = 1.0f, shape[j].colors[i][1] = 1.0f, shape[j].colors[i][2] = 1.0f;
					radius -= 0.001f;
				}
			}
		}
	}
	//glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	/*���� ��ȭ�ϴ� �Լ��� �־�δ� �뵵�� ���� �����*/
	

	glutTimerFunc(3, TimerFunction, 1);
	glutPostRedisplay();
}