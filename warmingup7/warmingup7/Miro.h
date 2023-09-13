#pragma once
#include "Header.h"
struct node {
	int x, y;
	int data;
	struct node* next;
	struct node* prev;
};
struct node* head=NULL;
struct node* tail;

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