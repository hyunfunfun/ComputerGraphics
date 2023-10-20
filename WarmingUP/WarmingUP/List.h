#pragma once
#include "Header.h"
struct Listarr {
	int x=NULL;
	int y=NULL;
	int z=NULL;
	bool check=false;
	float distance = 0.0;
};
struct List {
	int count=0;
	int ucount=0;
	Listarr liarr[10];
	Listarr aliarr[10];
	Listarr sliarr[10];
	Listarr temp;
	void plus(int x_, int y_, int z_);
	void minus();
	void e(int x_, int y_, int z_);
	void d();
	void l();
	void c();
	void m();
	void n();
	void a();
	void a2();
	void s();
	void s2();
};