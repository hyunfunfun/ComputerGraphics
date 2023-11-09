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
	//도형 변수
	bool xmode = false;
	float xmove;
	float ymove;
	bool check = false;
	int objectType = TRIANGLE;
};

struct Slice {
	float vertex[5][3];
	float color[5][3];

	GLuint vao, vbo[2];
	//도형 변수
	bool xmode = false;
	float xmove;
	float ymove;
	bool check = false;
	int objectType = TRIANGLE;
};


Slice sli[2];
Object obj[5];
GLfloat rColor = 0.5, gColor = 0.5, bColor = 1.0;

//선 변수
float prevx = 0;
float prevy = 0;


//바구니 변수
float basketmove = 0.0;
bool basketmode = true;

//도형 슬라이스
glm::vec3 cross1 = glm::vec3(0.0, 0.0, 0.0);
glm::vec3 cross2 = glm::vec3(0.0, 0.0, 0.0);
int slicecount = 0;
int firstcross = 0;
int lastcross = 0;

bool polymode = false;

float speed = 0.01;

float px, py = 0.0;

bool GetIntersectPoint(float x1, float x2, float y1, float y2);

//사각형
float vertex[][3] = {
	{-0.15,0.15,0.0},
	{-0.15, -0.15, 0.0},
	{0.15, -0.15, 0.0},
	{0.15,0.15,0.0}
	//{-0.15,0.15,0.0},

	//{0.15, -0.15, 0.0},
};
float colors[][3] = {
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
	{0.0,0.0,1.0},
};

//삼각형
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

float colors1[][3] = {
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,1.0,0.0},
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


/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid Timer(int value);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void slicevao();
void Drawbasket();
void Drawobject();
void Drawslice();
void Drawline();

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
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
	
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);

	glutCreateWindow("Drill10");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();

	/*초기화 함수*/
	make_shaderProgram();
	Initvbovao();

	/*콜백 함수*/
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
	/*vao vbo 자동 업데이트*/
	/*그리기*/
	Drawbasket();
	Drawobject();
	Drawslice();
	if (shape[1].check == true) {
		Drawline();
	}

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

	for (int i = 0; i < 2; i++)
	{
		glGenVertexArrays(1, &sli[i].vao);
		glGenBuffers(2, sli[i].vbo);

		glBindVertexArray(sli[i].vao);

		glBindBuffer(GL_ARRAY_BUFFER, sli[i].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sli[i].vertex), sli[i].vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, sli[i].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void Drawbasket()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	TR = glm::translate(TR, glm::vec3(basketmove, -0.7, 0.0)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR = glm::scale(TR, glm::vec3(2.0, 0.3, 1));

	//vertex.glsl에 modelTransform에 좌표를 넣기 때문에 전처럼 updatebuffer()함수(vao,vbo업데이트)함수를 쓰지 않아도 된다.
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

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

		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
		TR = glm::translate(TR, glm::vec3(obj[i].xmove, obj[i].ymove, 0.0)); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬

		//vertex.glsl에 modelTransform에 좌표를 넣기 때문에 전처럼 updatebuffer()함수(vao,vbo업데이트)함수를 쓰지 않아도 된다.
		unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(obj[i].vao);
		if (polymode == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glDrawArrays(GL_POLYGON, 0, obj[i].objectType);
	}
}

void Drawslice()
{
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

		glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
		TR = glm::translate(TR, glm::vec3(sli[0].xmove-0.1, sli[0].ymove, 0.0)); //--- x축으로 이동 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬

		unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(sli[0].vao);
		if (polymode == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glDrawArrays(GL_POLYGON, 0, sli[0].objectType);

		glm::mat4 TR1 = glm::mat4(1.0f); //--- 합성 변환 행렬
		TR1 = glm::translate(TR1, glm::vec3(sli[1].xmove+0.1, sli[1].ymove, 0.0)); //--- x축으로 이동 행렬
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변

		glBindVertexArray(sli[1].vao);
		if (polymode == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glDrawArrays(GL_POLYGON, 0, sli[1].objectType);
}
void Drawline()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬
	TR = glm::translate(TR, glm::vec3(0.0, 0.0, 0.0)); //--- x축으로 이동 행렬
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR = glm::rotate(TR, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬


	//vertex.glsl에 modelTransform에 좌표를 넣기 때문에 전처럼 updatebuffer()함수(vao,vbo업데이트)함수를 쓰지 않아도 된다.
	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

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
	if (sli[0].xmode == true) {
		sli[0].ymove -= 0.01;
		sli[1].ymove -= 0.01;
		if (sli[0].ymove < -1) {
			sli[0].xmode == false;
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
		for (int i = 0; i < 5; i++) {
			if (i < 3) {
				if(slicecount==0)//왼쪽 슬라이스 도형에 넣기
				{
					if (GetIntersectPoint(vertex[0][0] + obj[i].xmove, vertex[1][0] + obj[i].xmove, vertex[0][1] + obj[i].ymove, vertex[1][1] + obj[i].ymove) == true) {
						sli[0].vertex[0][0] = vertex[0][0] + obj[i].xmove;
						sli[0].vertex[0][1] = vertex[0][1] + obj[i].ymove;
						sli[0].vertex[1][0] = cross1.x;
						sli[0].vertex[1][1] = cross1.y;

						sli[1].vertex[0][0] = cross1.x;
						sli[1].vertex[0][1] = cross1.y;
						sli[1].vertex[1][0] = vertex[1][0] + obj[i].xmove;
						sli[1].vertex[1][1] = vertex[1][1] + obj[i].ymove;
						slicecount++;
						firstcross = 1;
					}
					else {
						sli[0].vertex[0][0] = vertex[0][0] + obj[i].xmove;
						sli[0].vertex[0][1] = vertex[0][1] + obj[i].ymove;
						sli[0].vertex[1][0] = vertex[1][0] + obj[i].xmove;
						sli[0].vertex[1][1] = vertex[1][1] + obj[i].ymove;
					}
					if (GetIntersectPoint(vertex[1][0] + obj[i].xmove, vertex[2][0] + obj[i].xmove, vertex[1][1] + obj[i].ymove, vertex[2][1] + obj[i].ymove) == true) {
						sli[0].vertex[1][0] = vertex[1][0] + obj[i].xmove;
						sli[0].vertex[1][1] = vertex[1][1] + obj[i].ymove;
						sli[0].vertex[2][0] = cross1.x;
						sli[0].vertex[2][1] = cross1.y;

						sli[1].vertex[0][0] = cross1.x;
						sli[1].vertex[0][1] = cross1.y;
						sli[1].vertex[1][0] = vertex[2][0] + obj[i].xmove;
						sli[1].vertex[1][1] = vertex[2][1] + obj[i].ymove;
						slicecount++;
						firstcross = 2;
					}
					else {
						sli[0].vertex[1][0] = vertex[1][0] + obj[i].xmove;
						sli[0].vertex[1][1] = vertex[1][1] + obj[i].ymove;
						sli[0].vertex[2][0] = vertex[2][0] + obj[i].xmove;
						sli[0].vertex[2][1] = vertex[2][1] + obj[i].ymove;
					}
					if (GetIntersectPoint(vertex[2][0] + obj[i].xmove, vertex[3][0] + obj[i].xmove, vertex[2][1] + obj[i].ymove, vertex[3][1] + obj[i].ymove) == true) {
						sli[0].vertex[2][0] = vertex[2][0] + obj[i].xmove;
						sli[0].vertex[2][1] = vertex[2][1] + obj[i].ymove;
						sli[0].vertex[3][0] = cross1.x;
						sli[0].vertex[3][1] = cross1.y;

						sli[1].vertex[0][0] = cross1.x;
						sli[1].vertex[0][1] = cross1.y;
						sli[1].vertex[1][0] = vertex[3][0] + obj[i].xmove;
						sli[1].vertex[1][1] = vertex[3][1] + obj[i].ymove;
						slicecount++;
						firstcross = 3;
					}
				}
				else if (slicecount == 1) {//오른쪽 슬라이스 도형에 넣기
					if (firstcross == 3) {
						if (GetIntersectPoint(vertex[3][0] + obj[i].xmove, vertex[0][0] + obj[i].xmove, vertex[3][1] + obj[i].ymove, vertex[0][1] + obj[i].ymove) == true) {
							sli[1].vertex[1][0] = vertex[3][0] + obj[i].xmove;
							sli[1].vertex[1][1] = vertex[3][1] + obj[i].ymove;
							sli[1].vertex[2][0] = cross2.x;
							sli[1].vertex[2][1] = cross2.y;

							sli[0].vertex[4][0] = cross2.x;
							sli[0].vertex[4][1] = cross2.y;
							sli[0].vertex[0][0] = vertex[0][0] + obj[i].xmove;
							sli[0].vertex[0][1] = vertex[0][1] + obj[i].ymove;
							slicecount++;
							lastcross = 4;
						}
					}
					if (firstcross == 2) {
						if (GetIntersectPoint(vertex[2][0] + obj[i].xmove, vertex[3][0] + obj[i].xmove, vertex[2][1] + obj[i].ymove, vertex[3][1] + obj[i].ymove) == true) {
							sli[1].vertex[1][0] = vertex[2][0] + obj[i].xmove;
							sli[1].vertex[1][1] = vertex[2][1] + obj[i].ymove;
							sli[1].vertex[2][0] = cross2.x;
							sli[1].vertex[2][1] = cross2.y;

							sli[0].vertex[3][0] = cross2.x;
							sli[0].vertex[3][1] = cross2.y;
							sli[0].vertex[4][0] = vertex[3][0] + obj[i].xmove;
							sli[0].vertex[4][1] = vertex[3][1] + obj[i].ymove;
							slicecount++;
							lastcross = 3;
						}
						else {
							sli[1].vertex[1][0] = vertex[2][0] + obj[i].xmove;
							sli[1].vertex[1][1] = vertex[2][1] + obj[i].ymove;
							sli[1].vertex[2][0] = vertex[3][0] + obj[i].xmove;
							sli[1].vertex[2][1] = vertex[3][1] + obj[i].ymove;
						}
						if (GetIntersectPoint(vertex[3][0] + obj[i].xmove, vertex[0][0] + obj[i].xmove, vertex[3][1] + obj[i].ymove, vertex[0][1] + obj[i].ymove) == true) {
							sli[1].vertex[2][0] = vertex[3][0] + obj[i].xmove;
							sli[1].vertex[2][1] = vertex[3][1] + obj[i].ymove;
							sli[1].vertex[3][0] = cross2.x;
							sli[1].vertex[3][1] = cross2.y;

							sli[0].vertex[3][0] = cross2.x;
							sli[0].vertex[3][1] = cross2.y;
							sli[0].vertex[4][0] = vertex[0][0] + obj[i].xmove;
							sli[0].vertex[4][1] = vertex[0][1] + obj[i].ymove;
							slicecount++;
							lastcross = 4;
						}
					}
					if (firstcross == 1) {
						if (GetIntersectPoint(vertex[1][0] + obj[i].xmove, vertex[2][0] + obj[i].xmove, vertex[1][1] + obj[i].ymove, vertex[2][1] + obj[i].ymove) == true) {
							sli[1].vertex[1][0] = vertex[1][0] + obj[i].xmove;
							sli[1].vertex[1][1] = vertex[1][1] + obj[i].ymove;
							sli[1].vertex[2][0] = cross2.x;
							sli[1].vertex[2][1] = cross2.y;

							sli[0].vertex[2][0] = cross2.x;
							sli[0].vertex[2][1] = cross2.y;
							sli[0].vertex[3][0] = vertex[2][0] + obj[i].xmove;
							sli[0].vertex[3][1] = vertex[2][1] + obj[i].ymove;
							slicecount++;
							lastcross = 2;
						}
						else {
							sli[1].vertex[1][0] = vertex[1][0] + obj[i].xmove;
							sli[1].vertex[1][1] = vertex[1][1] + obj[i].ymove;
							sli[1].vertex[2][0] = vertex[2][0] + obj[i].xmove;
							sli[1].vertex[2][1] = vertex[2][1] + obj[i].ymove;
						}
						if (GetIntersectPoint(vertex[2][0] + obj[i].xmove, vertex[3][0] + obj[i].xmove, vertex[2][1] + obj[i].ymove, vertex[3][1] + obj[i].ymove) == true) {
							sli[1].vertex[2][0] = vertex[2][0] + obj[i].xmove;
							sli[1].vertex[2][1] = vertex[2][1] + obj[i].ymove;
							sli[1].vertex[3][0] = cross2.x;
							sli[1].vertex[3][1] = cross2.y;

							sli[0].vertex[2][0] = cross2.x;
							sli[0].vertex[2][1] = cross2.y;
							sli[0].vertex[3][0] = vertex[3][0] + obj[i].xmove;
							sli[0].vertex[3][1] = vertex[3][1] + obj[i].ymove;
							slicecount++;
							lastcross = 3;
						}
						else {
							sli[1].vertex[2][0] = vertex[2][0] + obj[i].xmove;
							sli[1].vertex[2][1] = vertex[2][1] + obj[i].ymove;
							sli[1].vertex[3][0] = vertex[3][0] + obj[i].xmove;
							sli[1].vertex[3][1] = vertex[3][1] + obj[i].ymove;
						}
						if (GetIntersectPoint(vertex[3][0] + obj[i].xmove, vertex[0][0] + obj[i].xmove, vertex[3][1] + obj[i].ymove, vertex[0][1] + obj[i].ymove) == true) {
							sli[1].vertex[3][0] = vertex[3][0] + obj[i].xmove;
							sli[1].vertex[3][1] = vertex[3][1] + obj[i].ymove;
							sli[1].vertex[4][0] = cross2.x;
							sli[1].vertex[4][1] = cross2.y;

							sli[0].vertex[2][0] = cross2.x;
							sli[0].vertex[2][1] = cross2.y;
							sli[0].vertex[3][0] = vertex[0][0] + obj[i].xmove;
							sli[0].vertex[3][1] = vertex[0][1] + obj[i].ymove;
							slicecount++;
							lastcross = 4;
						}
					}
				}
				else {//교점을 이어준다.
					switch (firstcross) {
					case 1:
						if (lastcross == 2) {
							sli[0].objectType = PENTAGON;
							sli[1].objectType = TRIANGLE;
						}
						if (lastcross == 3) {
							sli[0].objectType = RECTANGLE;
							sli[1].objectType = RECTANGLE;
						}
						if (lastcross == 4) {
							sli[1].objectType = PENTAGON;
							sli[0].objectType = TRIANGLE;
						}
						break;
					case 2:
						if (lastcross == 3) {
							sli[0].objectType = PENTAGON;
							sli[1].objectType = TRIANGLE;
						}
						if (lastcross == 4) {
							sli[0].objectType = RECTANGLE;
							sli[1].objectType = RECTANGLE;
						}
						break;
					case 3:
						if (lastcross == 4) {
							sli[0].objectType = PENTAGON;
							sli[1].objectType = TRIANGLE;
						}
					}
					sli[0].xmode = true;
				}
			}
		}

		//vao에 넣을 slice좌표 조정
		slicevao();
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

bool GetIntersectPoint(float x1, float x2, float y1, float y2)
{
	float temp;
	if (linevertex[0][0] > linevertex[1][0]) {
		temp = linevertex[0][0];
		linevertex[0][0] = linevertex[1][0];
		linevertex[1][0] = temp;
	}
	if (linevertex[0][1] > linevertex[1][1]) {
		temp = linevertex[0][1];
		linevertex[0][1] = linevertex[1][1];
		linevertex[1][1] = temp;
	}
	double t;
	double s;
	double under = (y2 - y1) * (linevertex[1][0] - linevertex[0][0]) - (x2 - x1) * (linevertex[1][1] - linevertex[0][1]);
	if (under == 0) return false;

	double _t = (x2 - x1) * (linevertex[0][1] - y1) - (y2 - y1) * (linevertex[0][0] - x1);
	double _s = (linevertex[1][0] - linevertex[0][0]) * (linevertex[0][1] - y1) - (linevertex[1][1] - linevertex[0][1]) * (linevertex[0][0] - x1);

	t = _t / under;
	s = _s / under;

	if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0) return false;
	if (_t == 0 && _s == 0) return false;

	if (slicecount == 0) {
		cross1.x = linevertex[0][0] + t * (double)(linevertex[1][0] - linevertex[0][0]);
		cross1.y = linevertex[0][1] + t * (double)(linevertex[1][1] - linevertex[0][1]);
	}
	else if (slicecount == 1) {
		cross2.x = linevertex[0][0] + t * (double)(linevertex[1][0] - linevertex[0][0]);
		cross2.y = linevertex[0][1] + t * (double)(linevertex[1][1] - linevertex[0][1]);
	}

	return true;
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