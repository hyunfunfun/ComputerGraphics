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
	int check = 0;
	int ran3 = rand() % 20 + 10;
	while (1) {
		if(x<=49||y<=49) {
			int ran = (rand() % 4);
			for (int i = 0; i < ran; i++) {
				if (x >= 49&&y!=49) {
					for (int i = 1; i < ran; i++) {
						x--;
						board[y][x].check = true;
					}
				}
				if (y >= 49&&x!=49) {
					for (int i = 1; i < ran; i++) {
						y--;
						board[y][x].check = true;
					}
				}
				int ran2 = rand() % 2;
				switch (ran2) {
				case 0:
					if (check == 1) {
						check = 0;
						break;
					}
					else {
						board[y][x].check = true;
						x++;
						check = 1;
						break;
					}
				case 1:
					if (check == 0) {
						check = 1;
						break;
					}
					else {
						board[y][x].check = true;
						y++;
						check = 0;
						break;
					}
				}
			}
		}
		else {
			board[y][x].check = true;
			break;
		}
	}
}
void Miro::r() {

}
void Miro::plus() {

}
void Miro::minus() {

}
