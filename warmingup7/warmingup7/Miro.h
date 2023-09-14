#pragma once
#include "Header.h"

struct Board {
	bool check = false;
	int no;
};

struct Miro {
	Board board[50][50];
	bool dor = false;
	int sum;
	void showboard();
	void enter();
	void r();
	void plus();
	void minus();
};