#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLuint vbo[2], vao, ebo;
};

Shape s[4];

GLfloat spivertex[360][3] = { 0 };
GLfloat spicolors[360][3] = { 0 };
float colors[] = {
	   0.5f, 0.0f, 0.5f,//4
	   0.0f, 0.0f, 1.0f,//0
	   0.0f, 0.0f, 0.0f,//3

	   0.5f, 0.0f, 0.5f,//4
	   0.0f, 0.0f, 0.0f,//3
	   1.0f, 0.0f, 0.0f,//7

	   0.0f, 1.0f, 0.0f,//2
	   0.5f, 0.5f, 0.0f,//6
	   1.0f, 0.0f, 0.0f,//7

	   0.0f, 1.0f, 0.0f,//2
	   1.0f, 0.0f, 0.0f,//7
	   0.0f, 0.0f, 0.0f,//3

	   0.0f, 0.5f, 0.5f,//1
	   1.0f, 1.0f, 1.0f,//5
	   0.0f, 1.0f, 0.0f,//2

	   1.0f, 1.0f, 1.0f,//5
	   0.5f, 0.5f, 0.0f,//6
	   0.0f, 1.0f, 0.0f,//2

	   0.0f, 0.0f, 1.0f,//0
	   0.5f, 0.0f, 0.5f,//4
	   0.0f, 0.5f, 0.5f,//1

	   0.5f, 0.0f, 0.5f,//4
	   1.0f, 1.0f, 1.0f,//5
	   0.0f, 0.5f, 0.5f,//1

	   0.5f, 0.0f, 0.5f,//4
	   1.0f, 0.0f, 0.0f,//7
	   1.0f, 1.0f, 1.0f,//5

	   1.0f, 0.0f, 0.0f,//7
	   0.5f, 0.5f, 0.0f,//6
	   1.0f, 1.0f, 1.0f,//5

	   0.0f, 0.0f, 1.0f,//0
	   0.0f, 0.5f, 0.5f,//1
	   0.0f, 1.0f, 0.0f,//2

	   0.0f, 0.0f, 1.0f,//0
	   0.0f, 1.0f, 0.0f,//2
	   0.0f, 0.0f, 0.0f,//3
};
GLfloat line[][3] = {
	{0.0,1.0,0.0},
	{0.0,-1.0,0.0},
	{-1.0,0.0,0.0},
	{1.0,0.0,0.0},
	{0.0,0.0,1.0},
	{0.0,0.0,-1.0},
};
GLfloat linecolors[][3] = {
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0}
};

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

//스파이럴타이머
bool rtimer = false;
bool donespi = false;
int spicount = 1;

//t타이머
bool ttimer = false;
float disx1 = 0.0f;
float disz1 = 0.0f;
float disx2 = 0.0f;
float disz2 = 0.0f;
int t1 = 0;
int t2 = 0;


//1타이머
bool timer1 = false;

//2타이머
bool timer2 = false;
double rot = 0.0f;

//3타이머
bool timer3 = false;

bool select = false;
bool scale = false;

//위치,회전,신축
float x1Rotate = 30.0f;
float y1Rotate = -30.0f;
float x2Rotate = 30.0f;
float y2Rotate = -30.0f;

double x1move = -0.5;
double y1move = 0.0;
double x2move = 0.5;
double y2move = 0.0;
double z1move = 0.0;
double z2move = 0.0;

double scale1 = 0.2;
double scale2 = 0.2;

GLfloat radius = 0.1f;
GLfloat rColor = 1, gColor = 1, bColor = 1;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
GLvoid spiTimer(int value);
GLvoid spiTimer2(int value);
GLvoid TTimer(int value);
GLvoid Timer1(int value);
GLvoid Timer2(int value);
GLvoid Timer3(int value);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initvbovao();
void Draw();
void Drawleft();
void Drawright();
void Drawspi();

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

	srand(time(NULL));

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
	cout << "v:물체변경" << endl;
	cout << "za xs cd:물체이동"<<endl;
	cout << "vf:물체제자리신축" << endl;
	cout << "bg:물체원점신축" << endl;
    glutMainLoop();

    return 0;
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);
	
	/*그리기*/
	Draw();
	Drawleft();
	Drawright();
	if(rtimer==true)
		Drawspi();
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initvbovao()
{
	Load_Object("cube.obj");

	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");
	{
		glGenVertexArrays(1, &s[0].vao);
		glGenBuffers(2, s[0].vbo);
		glGenBuffers(1, &s[0].ebo);

		glBindVertexArray(s[0].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[0].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[0].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	Load_Object("sphere.obj");
	{
		glGenVertexArrays(1, &s[1].vao);
		glGenBuffers(1, s[1].vbo);
		glGenBuffers(1, &s[1].ebo);

		glBindVertexArray(s[1].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[1].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s[1].ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	{//line
		glGenVertexArrays(1, &s[2].vao);
		glGenBuffers(2, s[2].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[2].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[2].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolors), linecolors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}

	{
		for (int i = 0; i < 360; i++)
		{
			spivertex[i][0] = cos(i / 100.0f * (2.0f * 3.141592)) * radius;  // x좌표
			spivertex[i][2] = sin(i / 100.0f * (2.0f * 3.141592)) * radius;   // y좌표
			spicolors[i][0] = 1.0f, spicolors[i][1] = 0.0f, spicolors[i][2] = 0.0f;
			radius += 0.003f;
		}
		glGenVertexArrays(1, &s[3].vao);
		glGenBuffers(2, s[3].vbo);
		//glGenBuffers(1, &ebo);

		glBindVertexArray(s[3].vao);

		glBindBuffer(GL_ARRAY_BUFFER, s[3].vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(spivertex), spivertex, GL_STATIC_DRAW);
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, s[3].vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(spicolors), spicolors, GL_STATIC_DRAW);
		glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(PosLocation);
		glEnableVertexAttribArray(ColorLocation);
	}
}

void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{//line
		Tx = glm::translate(Tx, glm::vec3(0, 0, 0)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = Tx * Rz; //--- 합성 변환 행렬: 회전  이동

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[2].vao);
		glLineWidth(1);
		glDrawArrays(GL_LINES, 0, 6);

	}


	//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, (void*)0);
	//glDisableVertexAttribArray(PosLocation);
	//glDisableVertexAttribArray(ColorLocation);

}
void Drawleft() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		Tx = glm::translate(Tx, glm::vec3(x1move, y1move, z1move)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(x1Rotate), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(y1Rotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(scale1, scale1, scale1));
		if(scale==false)
			TR = Rz * Tx * Sx; //제자리 신축
		else if(scale==true)
			TR = Sx * Rz * Tx;  //원점 신축

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[0].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}
void Drawright() {
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		Tx = glm::translate(Tx, glm::vec3(x2move, y2move, z2move)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(x2Rotate), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(y2Rotate), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		Sx = glm::scale(Sx, glm::vec3(scale2, scale2, scale2));
		if (scale == false)
			TR = Rz * Tx * Sx; //제자리 신축
		else if (scale == true)
			TR = Sx * Rz * Tx;  //원점 신축

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[1].vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, 0);
	}
}

void Drawspi()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 Tx = glm::mat4(1.0f); //--- 이동 행렬 선언
	glm::mat4 Rz = glm::mat4(1.0f); //--- 회전 행렬 선언
	glm::mat4 Sx = glm::mat4(1.0f); //--- 크기 행렬 선언
	glm::mat4 TR = glm::mat4(1.0f); //--- 합성 변환 행렬

	{
		Tx = glm::translate(Tx, glm::vec3(0, 0, 0)); //--- x축으로 이동 행렬
		Rz = glm::rotate(Rz, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
		Rz = glm::rotate(Rz, glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
		TR = Tx * Rz; //--- 합성 변환 행렬: 회전  이동

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR)); //--- modelTransform 변수에 변

		glBindVertexArray(s[3].vao);
		if (spicount < 360) {
			++spicount;
			glDrawArrays(GL_LINE_STRIP, 0, spicount);
		}
		else
		{
			donespi = true;
			glDrawArrays(GL_LINE_STRIP, 0, 360);
		}
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

GLvoid spiTimer(int value){
	if (rtimer == true) {
		if(donespi==true)
		{
			x1move = spivertex[value][0];
			z1move = spivertex[value][2];
			value++;
		}
		glutPostRedisplay(); // 화면 재 출력
		glutTimerFunc(10, spiTimer, value);
	}
}
GLvoid spiTimer2(int value) {
	if (rtimer == true) {
		if (donespi == true)
		{
			x2move = spivertex[value][0];
			z2move = spivertex[value][2];
			value++;
		}
		glutPostRedisplay(); // 화면 재 출력
		glutTimerFunc(20, spiTimer2, value);
	}
}
GLvoid TTimer(int value) {
	if (ttimer == true) {
		if (t1 < 100) {
			x1move -= disx1;
			z1move -= disz1;
			t1++;
		}
		else if (t1 < 200) {
			x1move += disx1;
			z1move += disz1;
			t1++;
		}
		if (t2 < 100) {
			x2move -= disx2;
			z2move -= disz2;
			t2++;
		}
		else if (t2 < 200) {
			x2move += disx2;
			z2move += disz2;
			t2++;
		}
		glutPostRedisplay();
		glutTimerFunc(10, TTimer, 0);
	}
}

GLvoid Timer1(int value) {
	if (timer1 == true) {
		if (t1 < 100) {
			x1move -= disx1;
			z1move -= disz1;
			t1++;
		}
		else if (t1 < 200) {
			x1move += disx2;
			z1move += disz2;
			t1++;
		}
		if (t2 < 100) {
			x2move -= disx2;
			z2move -= disz2;
			t2++;
		}
		else if (t2 < 200) {
			x2move += disx1;
			z2move += disz1;
			t2++;
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer1, 0);
	}
}

GLvoid Timer2(int value) {
	if(timer2==true)
	{
		if (t1 < 100) {
			x1move += disx1;
			x2move += disx2;
			z1move += disz1;
			z2move += disz2;
			y1Rotate += rot*2;
			y2Rotate += rot*2;
			t1++;
			glutPostRedisplay();
			glutTimerFunc(10, Timer2, 0);
		}
	}
}

GLvoid Timer3(int value) {
	if (timer3 == true) {
		if (t1 < 100) {
			x1move -= disx1;
			y1move -= disx1;
			t1++;
		}
		else if (t1 < 200) {
			x1move += disx2;
			y1move += disx1;
			t1++;
		}
		if (t2 < 100) {
			x2move -= disx2;
			y2move -= disx2;
			t2++;
		}
		else if (t2 < 200) {
			x2move += disx1;
			y2move += disx2;
			t2++;
		}
		glutPostRedisplay();
		glutTimerFunc(10, Timer3, 0);
	}
}

GLvoid keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		select ? select = false : select = true;
		break;
	case 'z':
		select ? x1move -= 0.05 : x2move -= 0.05;
		break;
	case 'a':
		select ? x1move += 0.05 : x2move += 0.05;
		break;
	case 'x':
		select ? y1move -= 0.05 : y2move -= 0.05;
		break;
	case 's':
		select ? y1move += 0.05 : y2move += 0.05;
		break;
	case 'c':
		select ? z1move -= 0.05 : z2move -= 0.05;
		break;
	case 'd':
		select ? z1move += 0.05 : z2move += 0.05;
		break;
	case 'v':
		scale = false;
		select ? scale1 += 0.01 : scale2 += 0.01;
		break;
	case 'f':
		scale = false;
		select ? scale1 -= 0.01 : scale2 -= 0.01;
		break;
	case 'b':
		scale = true;
		select ? scale1 += 0.01 : scale2 += 0.01;
		break;
	case 'g':
		scale = true;
		select ? scale1 -= 0.01 : scale2 -= 0.01;
		break;
	case 'r':
		spicount = 0;
		donespi = false;
		rtimer ? rtimer = false : rtimer = true;
		ttimer = false;
		timer1 = false;
		timer2 = false;
		glutTimerFunc(10, spiTimer, 0);
		glutTimerFunc(20, spiTimer2, 0);
		break;
	case 't':
		t1 = 0;
		t2 = 0;
		disx1 = x1move / 100;
		disz1 = z1move / 100;
		disx2 = x2move / 100;
		disz2 = z2move / 100;
		rtimer = false;
		ttimer ? ttimer = false : ttimer = true;
		timer1 = false;
		timer2 = false;
		glutTimerFunc(10, TTimer, 0);
		break;
	case '1':
		t1 = 0;
		t2 = 0;
		disx1 = x1move / 100;
		disz1 = z1move / 100;
		disx2 = x2move / 100;
		disz2 = z2move / 100;
		rtimer = false;
		ttimer = false;
		timer1 ? timer1 = false : timer1 = true;
		timer2 = false;
		glutTimerFunc(10, Timer1, 0);
		break;
	case '2':
		x1move = -0.5;
		y1move = 0.0;
		x2move = 0.5;
		y2move = 0.0;
		z1move = 0.0;
		z2move = 0.0;
		t1 = 0;
		t2 = 0;
		disx1 = (-x1move - x2move)/100;
		disz1 = (-z1move - z2move)/100;
		disx2 = (-x2move - x1move)/100;
		disz2 = (-z2move - z1move)/100;
		rot = (atan2(x1move - x2move, z1move - z2move) * 180 / 3.14) / 100;
		rtimer = false;
		ttimer = false;
		timer1 = false;
		timer2 ? timer2 = false : timer2 = true;
		glutTimerFunc(10, Timer2, 0);
		break;
	case '3':
		t1 = 0;
		t2 = 0;
		disx1 = x1move / 100;
		disz1 = z1move / 100;
		disx2 = x2move / 100;
		disz2 = z2move / 100;
		rtimer = false;
		timer3 ? timer3 = false : timer3 = true;
		timer1 = false;
		timer2 = false;
		glutTimerFunc(10, Timer3, 0);
		break;
	}
	glutPostRedisplay();

}
