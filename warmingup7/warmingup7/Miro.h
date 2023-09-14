#pragma once
#include "Header.h"

struct Board {
	bool check = false;
	int no=0;
};

struct Miro {
	Board board[50][50];
	bool dor = false;
	int sum=0;
	void showboard();
	void enter();
	void r();
	void plus();
	void minus();
};