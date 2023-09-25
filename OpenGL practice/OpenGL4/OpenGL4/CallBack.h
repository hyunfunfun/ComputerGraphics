#pragma once
#include "Header.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);

GLvoid aTimer(int value);
GLvoid iTimer(int value);
GLvoid cTimer(int value);
GLvoid oTimer(int value);