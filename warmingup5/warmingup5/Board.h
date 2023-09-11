#pragma once

#include "Header.h"

struct Board {
	char x;
	int y;
	char data;
	bool check = false;
};
struct boardf {
	Board board[5][5];
	void prtboard();
	void inputxy();
	void inputup();
	void suffle();
	void inputxyO(int x1, int y1, int x2, int y2);
	void showen(char en, int x1, int y1, int x2, int y2);
};