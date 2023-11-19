#pragma once
#include <iostream>
#include <stdlib.h>
#include <random>
using namespace std;

random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_real_distribution<double> randomColor(0.0, 1.0);
uniform_int_distribution<int> randomMotionType1(1, 2);
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;
/*üũ ����*/
bool objectRotate;
bool lightRoate;
bool lightSwitch = true;
bool objectchange;
/*���� ��ȭ ����*/
float lightX = 0.0f, lightY = -0.1f, lightZ = 0.0f;
float lightRadians = 240.0f;
float lightRadiusZ = 0.0f;
/*���ؽ� �迭*/
float cubeVerticles[] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
	// �޸�
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	// �ո�
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
float pyramidVerticles[] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
	//�޸�
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.0f,  0.5f, -0.0f,  0.0f,  0.0f, -1.0f,
	 // �ո�
	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
	  //����
	  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,
	   //������
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,

		//�Ʒ�
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
};
/*ť��*/
class Cube
{
private:
	/*�迭 ����*/
	GLuint _vao, _vbo[2];
	/*��� ����*/
	glm::mat4 _mixMat = glm::mat4{ 1.0f };
	/*���� ��ȭ ����*/
	bool _Alive = false;
	float _rotateY = 0.0f;
public:
	Cube()
	{


	};
	/*��ü �ʱ�ȭ*/
	void SetAlive(bool alive);
	/*���� �ʱ�ȭ*/
	void InitBuffer();
	/*�׸���*/
	void Draw();
	/*���� ��ȭ*/
	void Transform();
	void Rotating();
	/*�ִϸ��̼�*/
	~Cube()
	{


	};
};
Cube cube;
/*����*/
class LightCube
{
private:
	/*�迭 ����*/
	GLuint _vao, _vbo[2];
	/*��� ����*/
	glm::mat4 _mixMat = glm::mat4{ 1.0f };
	/*���� ��ȭ ����*/
	bool _Alive = false;
	float _rotateY = 0.0f;
public:
	LightCube()
	{


	};
	/*��ü �ʱ�ȭ*/
	void SetAlive(bool alive);

	/*���� �ʱ�ȭ*/
	void InitBuffer();
	/*�׸���*/
	void Draw();
	/*���� ��ȭ*/
	void Transform();
	void Rotating();
	/*�ִϸ��̼�*/
	~LightCube()
	{


	};
};
LightCube lightCube;
/*�Ƕ�̵�*/
class Pyramid
{
private:
	/*�迭 ����*/
	GLuint _vao, _vbo[2];
	/*��� ����*/
	glm::mat4 _mixMat = glm::mat4{ 1.0f };
	/*���� ��ȭ ����*/
	bool _Alive = false;
	float _rotateY = 0.0f;
public:
	Pyramid()
	{


	};
	/*��ü �ʱ�ȭ*/
	void SetAlive(bool alive);
	/*���� �ʱ�ȭ*/
	void InitBuffer();
	/*�׸���*/
	void Draw();
	/*���� ��ȭ*/
	void Transform();
	void Rotating();
	/*�ִϸ��̼�*/
	~Pyramid()
	{


	};
};
Pyramid pyramid;