#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

struct Shape {
	GLuint vbo[2], vao, ebo;
};

Shape s[4];

std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;

double xMove = 0.0, yMove = 0.0, zMove = 0.0;


GLfloat rColor = 0, gColor = 0, bColor = 0;

GLint width, height;
GLuint shaderProgramID;
GLuint vertexShader;
GLuint fragmentShader;
GLchar* vertexSource, * fragmentSource;

int lightmode = 0;
float yAngle = 0.0f;
float dis = 2.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); //--- 카메라 위치
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

glm::vec3 lightPosition(0.0f, 3.0f, 0.0f);

/*OPGL관렴 함수*/
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int w, int h);

/*셰이더 관련 함수*/
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();

/*vao, vbo 관련 함수*/
void Initbuffer();
void light();
void Draw();

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
		printf("파일 경로 확인\n");
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
				printf("못읽");
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
	Initbuffer();
	light();
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();

	return 0;
}

GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glUseProgram(shaderProgramID);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 50.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0));
	unsigned int projectionLocation = glGetUniformLocation(shaderProgramID, "projection"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glm::mat4 view = glm::mat4(1.0f);
	cameraPos.y = 3.0;
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderProgramID, "view"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	/*그리기*/
	Draw();

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Initbuffer() {

	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int NormalLocation = glGetAttribLocation(shaderProgramID, "vNormal");
	{
		ReadObj("sphere.obj");
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
		ReadObj("sphere.obj");
		{
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

		ReadObj("sphere.obj");
		{
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
	}
}
void light() {
	glUseProgram(shaderProgramID);
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}
void Draw()
{
	int PosLocation = glGetAttribLocation(shaderProgramID, "vPos");
	int ColorLocation = glGetAttribLocation(shaderProgramID, "vNormal");

	unsigned int modelLocation = glGetUniformLocation(shaderProgramID, "model"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 TR1 = glm::mat4(1.0f); //--- 합성 변환 행렬
	TR1 = glm::translate(TR1, glm::vec3(xMove, yMove, zMove)); //--- x축으로 이동 행렬
	TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR1 = glm::rotate(TR1, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR1)); //--- modelTransform 변수에 변

	unsigned int objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");
	glUniform3f(objColorLocation, 1.0, 0.0, 0.0);

	glBindVertexArray(s[0].vao);

	glDrawArrays(GL_TRIANGLES, 0, 10000);

	glm::mat4 TR2 = glm::mat4(1.0f); //--- 합성 변환 행렬
	TR2 = glm::translate(TR2, glm::vec3(xMove-1.0, yMove, zMove)); //--- x축으로 이동 행렬
	TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR2 = glm::rotate(TR2, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR2 = glm::scale(TR2, glm::vec3(0.7, 0.7, 0.7)); //--- x축으로 이동 행렬

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR2)); //--- modelTransform 변수에 변

	glUniform3f(objColorLocation, 0.0, 1.0, 0.0);

	glBindVertexArray(s[1].vao);

	glDrawArrays(GL_TRIANGLES, 0, 10000);


	glm::mat4 TR3 = glm::mat4(1.0f); //--- 합성 변환 행렬
	TR3 = glm::translate(TR3, glm::vec3(xMove - 1.5, yMove, zMove)); //--- x축으로 이동 행렬
	TR3 = glm::rotate(TR3, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0)); //--- x축에 대하여 회전 행렬
	TR3 = glm::rotate(TR3, glm::radians(0.0f), glm::vec3(0.0, 1.0, 0.0)); //--- y축에 대하여 회전 행렬
	TR3 = glm::scale(TR3, glm::vec3(0.4, 0.4, 0.4)); //--- x축으로 이동 행렬

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR3)); //--- modelTransform 변수에 변

	glUniform3f(objColorLocation, 0.0, 0.0, 1.0);

	glBindVertexArray(s[2].vao);

	glDrawArrays(GL_TRIANGLES, 0, 10000);

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
	vertexSource = filetobuf("vertex1.glsl");
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
	fragmentSource = filetobuf("fragment1.glsl");
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

GLvoid Keyboard(unsigned char key, int w, int h) {
	unsigned int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	switch (key) {
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
	case 'r':
		yAngle += 0.1;
		glUniform3f(lightPosLocation, dis * sin(yAngle), 0.0, dis * cos(yAngle));
		break;
	case 'R':
		yAngle -= 0.1;
		glUniform3f(lightPosLocation, dis * sin(yAngle), 0.0, dis * cos(yAngle));
		break;
	}
	glutPostRedisplay();
}