#include "Header.h"
#include "Miro.h"

void Miro::showboard() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (board[i][j].check == true) {
				cout << "0 ";
			}
			else {
				cout << "1 ";
			}
		}
		cout << endl;
	}
}
void Miro::enter() {
	int x=0, y=0;
	int data = 0;
	while (1) {
		if (x > 49 && y > 49) {
			break;
		}
		else {
			struct node* newnode = new node;
			newnode->x = x;
			newnode->y = y;
			newnode->data = data;
			newnode->next = NULL;
			board[x][y].check = true;
			data++;
			x++;
			y++;
			node* cur;
			cur = head->next;
			while (cur->data < data && cur != tail) {
				cur = cur->next;
			}
			node* prev = cur->prev;
			prev->next = newnode;
			newnode->prev = prev;
			cur->prev = newnode;
			newnode->next = cur;
		}
	}

}
void Miro::r() {

}
void Miro::plus() {

}
void Miro::minus() {

}
