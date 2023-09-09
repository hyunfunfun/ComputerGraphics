#pragma once
#include "Header.h"
struct Listarr {
	int x=NULL;
	int y=NULL;
	int z=NULL;
};
struct List {
	int count;
	Listarr liarr[10];
	void plus(int x_, int y_, int z_);
	void minus();
	void e(int x_, int y_, int z_);
	void d();
	void l();
	void c();
	void m();
	void n();
	void a();
	void s();
};