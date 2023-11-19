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
/*체크 변수*/
bool objectRotate;
bool lightRoate;
bool lightSwitch = true;
bool objectchange;
/*상태 변화 변수*/
float lightX = 0.0f, lightY = -0.1f, lightZ = 0.0f;
float lightRadians = 240.0f;
float lightRadiusZ = 0.0f;
/*버텍스 배열*/
float cubeVerticles[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
	// 뒷면
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	// 앞면
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
float pyramidVerticles[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
	//뒷면
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.0f,  0.5f, -0.0f,  0.0f,  0.0f, -1.0f,
	 // 앞면
	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
	  //왼쪽
	  -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,
	   //오른쪽
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,

		//아래
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
};
/*큐브*/
class Cube
{
private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	/*행렬 관련*/
	glm::mat4 _mixMat = glm::mat4{ 1.0f };
	/*상태 변화 관련*/
	bool _Alive = false;
	float _rotateY = 0.0f;
public:
	Cube()
	{


	};
	/*객체 초기화*/
	void SetAlive(bool alive);
	/*버퍼 초기화*/
	void InitBuffer();
	/*그리기*/
	void Draw();
	/*상태 변화*/
	void Transform();
	void Rotating();
	/*애니메이션*/
	~Cube()
	{


	};
};
Cube cube;
/*조명*/
class LightCube
{
private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	/*행렬 관련*/
	glm::mat4 _mixMat = glm::mat4{ 1.0f };
	/*상태 변화 관련*/
	bool _Alive = false;
	float _rotateY = 0.0f;
public:
	LightCube()
	{


	};
	/*객체 초기화*/
	void SetAlive(bool alive);

	/*버퍼 초기화*/
	void InitBuffer();
	/*그리기*/
	void Draw();
	/*상태 변화*/
	void Transform();
	void Rotating();
	/*애니메이션*/
	~LightCube()
	{


	};
};
LightCube lightCube;
/*피라미드*/
class Pyramid
{
private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	/*행렬 관련*/
	glm::mat4 _mixMat = glm::mat4{ 1.0f };
	/*상태 변화 관련*/
	bool _Alive = false;
	float _rotateY = 0.0f;
public:
	Pyramid()
	{


	};
	/*객체 초기화*/
	void SetAlive(bool alive);
	/*버퍼 초기화*/
	void InitBuffer();
	/*그리기*/
	void Draw();
	/*상태 변화*/
	void Transform();
	void Rotating();
	/*애니메이션*/
	~Pyramid()
	{


	};
};
Pyramid pyramid;