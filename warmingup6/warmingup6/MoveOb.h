#pragma once
#include "Header.h"

struct Ob {
	bool check=false;
};
struct MoveOb {
	Ob ob[30][30];
	int boardx1, boardx2, boardy1, boardy2;
	int overx1=-1, overy1=-1;
	int overx2 = -1, overy2 = -1;
	void showboard();
	void changedata();
	void x();
	void X();
	void y();
	void Y();
	void s();
	void S();
	void i();
	void j();
	void k();
	void l();
	void R();
};