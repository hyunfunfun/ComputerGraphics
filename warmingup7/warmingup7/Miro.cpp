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
	int ran;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (i == j) {
				board[i][j].check = true;
			}
			ran=rand() % 4 + 1;
		}
	}
}
void Miro::r() {

}
void Miro::plus() {

}
void Miro::minus() {

}
