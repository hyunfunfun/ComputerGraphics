#pragma once
#include "Header.h"

struct Board {
	bool check = false;
};

struct Miro {
	Board board[50][50];
	void showboard();
	void enter();
	void r();
	void plus();
	void minus();
};