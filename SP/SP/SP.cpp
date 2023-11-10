#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

enum objecType
{
	TRIANGLE = 3,
	RECTANGLE = 4,
	PENTAGON = 5
};

struct Shape {
	GLuint vao, vbo[2];
	bool check=false;
};

Shape shape[2];

struct Object {
	GLuint vao, vbo[2];
	//���� ����
	bool xmode = false;
	bool check = true;
	float xmove;
	float ymove;
	int objectType = TRIANGLE;
};

struct Slice {
	float vertex[5][3];
	float color[5][3];

	GLuint vao, vbo[2];
	bool xmode = false;
	bool check = true;
	float xmove=0.0;
	float ymove=0.0;
	int objectType = TRIANGLE;
};

Slice sli[10];
Object obj[5];
GLfloat rColor = 0.5, gColor = 0.5, bColor = 1.0;

//�� ����
float prevx = 0;
float prevy = 0;


//�ٱ��� ����
float basketmove = 0.0;
bool basketmode = true;


bool polymode = false;
int slicecount = 0;
int sliceobj = 0;
float speed = 0.01;

bool GetIntersectPoint(float x1, float x2, float y1, float y2);

//�簢��
float vertex[][3] = {
	{-0.15,0.15,0.0},
	{-0.15, -0.15, 0.0},
	{0.15, -0.15, 0.0},
	{0.15,0.15,0.0}
};
float colors1[][3] = {
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
};

float colors[][3] = {
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
};

float slicevertex1[][3] = {
	{-0.15,0.15,0.0},
	{-0.15, -0.15, 0.0},
	{0.15,0.15,0.0}
};
float slicevertex2[][3] = {
	{-0.15, -0.15, 0.0},
	{0.15, -0.15, 0.0},
	{0.15,0.15,0.0}
};

//�ﰢ��
float vertex1[][3] = {
	{-0.15, 0.0, 0.0},
	{0.15, 0.0, 0.0},
	{0.0,0.3,0.0},

};
float colors2[][3] = {
	{1.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,0.0,1.0},
};

float slicevertex3[][3] = {
	{-0.15, 0.0, 0.0},
	{0.0, 0.0, 0.0},
	{0.0,0.3,0.0}
};
float slicevertex4[][3] = {
	{0.0, 0.0, 0.0},
	{0.15, 0.0, 0.0},
	{0.0,0.3,0.0}
};


float linevertex[2][3];
float linecolors[2][3] = {
	{0.0,0.0,0.0},
	{0.0,0.0,0.0}
};

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
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

/*���̴� ���� �Լ�*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo ���� �Լ�*/
void Initvbovao();
void slicevao();
void Drawbasket();
void Drawobject();
void Drawslice();
void Drawline();

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	srand(time(NULL));
	width = 800;
	height = 800;

	obj[0].ymove = rand()%10*0.1;
	obj[0].xmove = rand() % 2;
	if (obj[0].xmove == 0)
	{
		obj[0].xmove = -1;
		obj[0].xmode = true;
	}
	else {
		obj[0].xmode = false;
	}
	
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
	glutMotionFunc(Motion);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(10, Timer, 1);
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
	/*�׸���*/
	Drawbasket();
	if (obj[1].check == true) {
		Drawobject();
	}
	Drawslice();
	if (shape[1].check == true) {
		Drawline();
	}

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
		glGenVertexArrays(1, &shape[0].vao);
		glGenBuffers(2, shape[0].vbo);

		glBindVertexArray(shape[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, shape[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, shape[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
	{
		for (int i = 0; i < 5; i++)
		{
			glGenVertexArrays(1, &obj[i].vao);
			glGenBuffers(2, obj[i].vbo);

			glBindVertexArray(obj[i].vao);

			if (i < 3) {
				glBindBuffer(GL_ARRAY_BUFFER, obj[i].vbo[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, obj[i].vbo[1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
				obj[i].objectType = RECTANGLE;
			}
			else {
				glBindBuffer(GL_ARRAY_BUFFER, obj[i].vbo[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ARRAY_BUFFER, obj[i].vbo[1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(colors2), colors2, GL_STATIC_DRAW);
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
				obj[i].objectType = TRIANGLE;
			}


			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(ColorLocation);
		}
	}
}

void slicevao() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	
	glGenVertexArrays(1, &sli[sliceobj-1].vao);
	glGenBuffers(2, sli[sliceobj - 1].vbo);

	glBindVertexArray(sli[sliceobj - 1].vao);

	glBindBuffer(GL_ARRAY_BUFFER, sli[sliceobj - 1].vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sli[sliceobj - 1].vertex), sli[sliceobj - 1].vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, sli[sliceobj - 1].vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sli[sliceobj - 1].color), sli[sliceobj - 1].color, GL_STATIC_DRAW);
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	sli[sliceobj-1].objectType == TRIANGLE;

	glBindVertexArray(sli[sliceobj].vao);
	glBindBuffer(GL_ARRAY_BUFFER, sli[sliceobj].vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sli[sliceobj].vertex), sli[sliceobj].vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, sli[sliceobj].vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sli[sliceobj].color), sli[sliceobj].color, GL_STATIC_DRAW);
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	sli[sliceobj].objectType == TRIANGLE;
	glEnableVertexAttribArray(PosLocation);
	glEnableVertexAttribArray(ColorLocation);
}

void Drawbasket()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	TR = glm::translate(TR, glm::vec3(basketmove, -0.7, 0.0)); //--- x������ �̵� ���
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���
	TR = glm::scale(TR, glm::vec3(2.0, 0.3, 1));

	//vertex.glsl�� modelTransform�� ��ǥ�� �ֱ� ������ ��ó�� updatebuffer()�Լ�(vao,vbo������Ʈ)�Լ��� ���� �ʾƵ� �ȴ�.
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

	glBindVertexArray(shape[0].vao);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_POLYGON, 0, 4);
}
void Drawobject()
{
	for(int i=0;i<5;i++)
	{
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

		glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
		TR = glm::translate(TR, glm::vec3(obj[i].xmove, obj[i].ymove, 0.0)); //--- x������ �̵� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���

		//vertex.glsl�� modelTransform�� ��ǥ�� �ֱ� ������ ��ó�� updatebuffer()�Լ�(vao,vbo������Ʈ)�Լ��� ���� �ʾƵ� �ȴ�.
		unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

		glBindVertexArray(obj[i].vao);
		if (polymode == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glDrawArrays(GL_POLYGON, 0, obj[i].objectType);
	}
}

void Drawline()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glm::mat4 TR = glm::mat4(1.0f); //--- �ռ� ��ȯ ���
	TR = glm::translate(TR, glm::vec3(0.0, 0.0, 0.0)); //--- x������ �̵� ���
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x�࿡ ���Ͽ� ȸ�� ���
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y�࿡ ���Ͽ� ȸ�� ���


	//vertex.glsl�� modelTransform�� ��ǥ�� �ֱ� ������ ��ó�� updatebuffer()�Լ�(vao,vbo������Ʈ)�Լ��� ���� �ʾƵ� �ȴ�.
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform ������ ��

	glBindVertexArray(shape[1].vao);
	glDrawArrays(GL_LINES, 0, 2);
}

GLvoid Timer(int value) {
	if (basketmode == true) {
		basketmove -= 0.01;
		if (basketmove < -1)
			basketmode = false;
	}
	else {
		basketmove += 0.01;
		if (basketmove > 1)
			basketmode = true;
	}

	for(int i=0;i<5;i++)
	{
		if (obj[i].xmode == false)
			obj[i].xmove -= speed;
		if (obj[i].xmode == true)
			obj[i].xmove += speed;
		obj[i].ymove -= speed;
		if (obj[i].ymove < -1) {
			obj[i].ymove = rand() % 10 * 0.1;
			obj[i].xmove = rand() % 2;
			if (obj[i].xmove == 0)
			{
				obj[i].xmove = -1;
				obj[i].xmode = true;
			}
			else {
				obj[i].xmode = false;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
}

GLvoid Mouse(int button, int state, int x, int y) {
	float ox = (float)x / 400 - 1;
	float oy = -((float)y / 400 - 1);
	prevx = ox;
	prevy = oy;
	float range = 0.1;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		shape[1].check = true;
		linevertex[1][0] = ox;
		linevertex[1][1] = oy;
		linevertex[0][0] = ox;
		linevertex[0][1] = oy;
		//vao
		{
			int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
			int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
			glGenVertexArrays(1, &shape[1].vao);
			glGenBuffers(2, shape[1].vbo);

			glBindVertexArray(shape[1].vao);

			glBindBuffer(GL_ARRAY_BUFFER, shape[1].vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(linevertex), linevertex, GL_STATIC_DRAW);
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, shape[1].vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(linecolors), linecolors, GL_STATIC_DRAW);
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


			glEnableVertexAttribArray(PosLocation);
			glEnableVertexAttribArray(ColorLocation);
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		shape[1].check = false;
	}
}

GLvoid Motion(int x, int y) {
	float ox = (float)x / 400 - 1;
	float oy = -((float)y / 400 - 1);

	linevertex[1][0] = ox;
	linevertex[1][1] = oy;
	//vao
	{
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
		glGenVertexArrays(1, &shape[1].vao);
		glGenBuffers(2, shape[1].vbo);

		glBindVertexArray(shape[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, shape[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linevertex), linevertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, shape[1].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolors), linecolors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);


		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	glutPostRedisplay();
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'l':
		polymode ? polymode = false : polymode = true;
		break;
	case '+':
		speed += 0.0001;
		break;
	case '-':
		speed -= 0.0001;
		break;
	}
	glutPostRedisplay();
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