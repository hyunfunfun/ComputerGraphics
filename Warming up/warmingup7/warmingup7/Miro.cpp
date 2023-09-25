#include "Header.h"
#include "Miro.h"

void Miro::showboard() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (board[i][j].check == true && dor == true && sum == board[i][j].no) {
				cout << "* ";
			}
			else if (board[i][j].check == true) {
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
	sum = 0;
	dor = false;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			board[i][j].check = false;
			board[i][j].no = 0;
			
		}
	}
	bool chup = false;
	bool chleft = false;
	while (1) {
		if (x >= 49 && y >= 49) {
			board[y][x].check = true;
			board[y][x].no = sum;
			break;
		}
		else {
			if (x == 0 && y == 0) {
				board[y][x].no = sum;
				sum++;
				board[y][x].check = true;
				x++;
				board[y][x].check = true;
				board[y][x].no = sum;
				sum++;
			}
			else if (x == 49) {
				if (board[y][x-1].check == true) {
					sum++;
					board[y][x].no = sum;
					y++;
					board[y][x].check = true;
				}
				else {
					x--;
					sum++;
					board[y][x].no = sum;
					board[y][x].check = true;
				}
			}
			else if (y == 49) {
				if (board[y-1][x].check == true) {
					x++;
					sum++;
					board[y][x].no = sum;
					board[y][x].check = true;
				}
				else {
					y--;
					sum++;
					board[y][x].no = sum;
					board[y][x].check = true;
				}
			}

			else {
				int ran = rand() % 4;
				switch (ran) {
				case 0:
					if (board[y][x + 1].check == false) {
						if (x + 1 > 49) {
							break;
						}
						else {
							x++;
							board[y][x].check = true;
							sum++;
							board[y][x].no = sum;
							chup = false;
							break;
						}
					}
					else {
						break;
					}
				case 1:
					if (board[y][x - 1].check == false) {
						if (x -1 < 0) {
							break;
						}
						else {
							if (chup != true) {
								x--;
								board[y][x].check = true;
								sum++;
								board[y][x].no = sum;
								chleft = true;
								break;
							}
						}
					}
					else {
						break;
					}
				case 2:
					if (board[y + 1][x].check == false) {
						if (y + 1 > 49) {
							break;
						}
						else {
							y++;
							board[y][x].check = true;
							sum++;
							board[y][x].no = sum;
							chleft = false;
							break;
							
						}
					}
					else {
						break;
					}
				case 3:
					if (board[y - 1][x].check == false) {
						if (y - 1 < 0) {
							break;
						}
						else {
							if (chleft != true) {
								y--;
								board[y][x].check = true;
								chup = true;
								sum++;
								board[y][x].no = sum;
								break;
							}
							else {

							}
						}
					}
					else {
						break;
					}
				}
			}

		}
	}
	sum = 0;
}
void Miro::r() {
	dor = true;
	sum = 0;
}
void Miro::plus() {

	sum++;
}
void Miro::minus() {
	sum--;
}
