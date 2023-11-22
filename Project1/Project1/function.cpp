#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "header.h"
using namespace std;

/***********************�ݹ� �Լ�***********************/
GLvoid drawScene()
{
	/*���� ȭ��*/
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/******************************************************************/

	/*���̴� ���α׷� ���*/
	glUseProgram(shaderID);


	/*�׸���*/
	Draw();

	/******************************************************************/

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char button, int x, int y)
{
	unsigned int lightSwitchLocation = glGetUniformLocation(shaderID, "lightSwitch");
	switch (button)
	{
	case 'n':
		objectchange ? objectchange = false : objectchange = true;
		break;
	case 'm':
		lightSwitch ? lightSwitch = false : lightSwitch = true;
		/*���̴�: ���� ����ġ �ֱ�*/
		if (lightSwitch == true) {
			glUniform1i(lightSwitchLocation, 0);
		}
		else
		{
			glUniform1i(lightSwitchLocation, 1);
		}
		break;
	case 'y':
		objectRotate ? objectRotate = false : objectRotate = true;
		break;
	case 'r':
		lightRoate ? lightRoate = false : lightRoate = true;
		break;
	case 'z':
		lightRadiusZ += 0.1f;
		break;
	case 'Z':
		lightRadiusZ -= 0.1f;
		break;
	case 'q':
		exit(1);
		break;
	}
	glutPostRedisplay();
}
GLvoid TimerFunction(int value)
{
	/*��ȭ�ؾ� �� �κ�*/
	if (objectRotate == true) {
		cube.Rotating();
		pyramid.Rotating();
	}

	if (lightRoate == true) {
		lightRadians += 0.1f;
		if (lightRadians >= 360.0f) {
			lightRadians = 0.0f;
		}
	}

	/*Update�� Drawȣ��*/
	glutPostRedisplay();
	/*Ÿ�̸� ���� �ݺ�*/
	glutTimerFunc(50, TimerFunction, 1);
}
/***********************�ʱ�ȭ �Լ�***********************/
void InitObject()
{
	cube.SetAlive(true);
	pyramid.SetAlive(true);
	lightCube.SetAlive(true);
}
void InitBuffer()
{
	cube.InitBuffer();
	pyramid.InitBuffer();
	lightCube.InitBuffer();
}
/*********************ȭ�� ��� �Լ�**********************/
void Draw()
{
	/*ī�޶� ��ȯ*/
	CameraTransform();
	/*���� ��ȯ*/
	LightTransform();
	if (objectchange == false) {
		/*CUBE �׸���*/
		cube.Draw();
	}
	else
	{
		pyramid.Draw();
	}
	/*���� �׸���*/
	lightCube.Draw();
}
/********************ī�޶� ��ȯ �Լ�********************/
void CameraTransform()
{
	/*ī�޶� ����*/
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f); //--- ī�޶� ��ġ�� �� ��ǥ�� ����
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����. ��� �� ���⸸ �ٶ󺻴�.
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(shaderID, "view"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//��������
	unsigned int projLoc = glGetUniformLocation(shaderID, "projection");
	glm::mat4 pTransform = glm::mat4(1.0f);

	//��Ⱦ�� 1:1�� ����, ���� �þ߰� 60', z������ 5.0��ŭ �÷ȴ�.
	pTransform = glm::perspective(glm::radians(60.0f), (float)800 / (float)800, 0.1f, 500.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &pTransform[0][0]);
}
/*********************���� ��ȯ �Լ�*********************/
void LightTransform()
{
	/*���� ��ǥ*/
	lightX = 1.0f * cos(lightRadians);
	lightZ = (1.0f + lightRadiusZ) * sin(lightRadians);
	/*���̴�: ���� ��ǥ �ֱ�*/
	unsigned int lightPosLocation = glGetUniformLocation(shaderID, "lightPos");
	glUniform3f(lightPosLocation, lightX, lightY, lightZ);
	/*�ں��Ʈ ��*/
	unsigned int lightColorLocation = glGetUniformLocation(shaderID, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
}
/********************Class::Cube �Լ�********************/
void Cube::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint nAttribute = glGetAttribLocation(shaderID, "vNormal");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticles), cubeVerticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(nAttribute);
}
void Cube::Draw()
{
	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		/*������ ��*/
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, 0.0f, 1.0f, 0.0f);

		GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
		GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void Cube::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;

}
void Cube::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	_mixMat = glm::rotate(_mixMat, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_mixMat = glm::rotate(_mixMat, glm::radians(30.0f + _rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	_mixMat = glm::scale(_mixMat, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void Cube::Rotating()
{
	_rotateY += 10.0f;
	if (_rotateY >= 360.0f) {
		_rotateY = 0.0f;
	}
}
/********************Class::LightCube �Լ�********************/
void LightCube::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint nAttribute = glGetAttribLocation(shaderID, "vNormal");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticles), cubeVerticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(nAttribute);
}
void LightCube::Draw()
{
	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		/*������ ��*/
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, 0.5f, 0.5f, 0.5f);

		GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
		GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void LightCube::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;

}
void LightCube::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	_mixMat = glm::translate(_mixMat, glm::vec3(0.0f + lightX, 0.0f + lightY, 0.0f + lightZ));
	_mixMat = glm::rotate(_mixMat, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_mixMat = glm::rotate(_mixMat, glm::radians(30.0f + _rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	_mixMat = glm::scale(_mixMat, glm::vec3(0.3f, 0.3f, 0.3f));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void LightCube::Rotating()
{
	_rotateY += 10.0f;
	if (_rotateY >= 360.0f) {
		_rotateY = 0.0f;
	}
}

/********************Class::Pyramid �Լ�********************/
void Pyramid::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint nAttribute = glGetAttribLocation(shaderID, "vNormal");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVerticles), pyramidVerticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(nAttribute);
}
void Pyramid::Draw()
{
	/*������ ��*/

	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, 0.0f, 0.0f, 1.0f);

		GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
		GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawArrays(GL_TRIANGLES, 0, 18);
	}
}
void Pyramid::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;

}
void Pyramid::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	_mixMat = glm::rotate(_mixMat, glm::radians(30.0f + _rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	_mixMat = glm::scale(_mixMat, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void Pyramid::Rotating()
{
	_rotateY += 10.0f;
	if (_rotateY >= 360.0f) {
		_rotateY = 0.0f;
	}
}














































/**************************���̴� ���α׷�**************************/
void make_vertexShader()
{
	GLchar* vertexSource;
	GLint result;
	GLchar errorLog[512];
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShader()
{
	GLchar* fragmentSource;
	GLint result;
	GLchar errorLog[512];
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("fragment.glsl"); // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_shaderProgram()
{
	GLchar errorLog[512];
	GLint result;
	make_vertexShader();
	make_fragmentShader();

	//-- shader Program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ---���̴��� �� ����Ǿ����� üũ�ϱ�
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		return;
	}

	//--- Shader Program ����ϱ�
	glUseProgram(shaderID);
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
