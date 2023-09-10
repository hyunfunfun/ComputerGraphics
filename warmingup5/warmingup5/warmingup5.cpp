#include "Header.h"

struct board {
	char x;
	int y;
	bool check = false;
};

int main() {

	board board[5][5];

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			switch (i) {
			case 1:
				board[i][j].y = 1;
				break;
			case 2:
				board[i][j].y = 2;
				break;
			case 3:
				board[i][j].y = 3;
				break;
			case 4:
				board[i][j].y = 4;
				break;
			}
			switch (j) {
			case 1:
				board[i][j].x = 'a';
				break;
			case 2:
				board[i][j].x = 'b';
				break;
			case 3:
				board[i][j].x = 'c';
				break;
			case 4:
				board[i][j].x = 'd';
				break;
			}
		}
		cout << endl;
	}

	char n;
	char x1, x2;
	int y1, y2;
	char en;



	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 && j == 0) {
				cout << " ";
			}
			else if (i == 0) {
				cout << " " << board[i][j].x << " ";
			}
			else if (j == 0) {
				cout << board[i][j].y;
			}
			else {
				cout << " * ";
			}
		}
		cout << endl;
	}

	while (1) {
		cout << "1¹øÁÂÇ¥ÀÔ·Â"<<endl;
		x1 = _getch();
		y1 = _getch()-48;


		cout << "2¹øÁÂÇ¥ÀÔ·Â"<<endl;
		x2 = _getch();
		y2 = _getch()-48;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (i == 0 && j == 0) {
					cout << " ";
				}
				else if (i == 0) {
					cout << " " << board[i][j].x << " ";
				}
				else if (j == 0) {
					cout << board[i][j].y;
				}
				else if ((board[i][j].x == x1 && board[i][j].y == y1) || (board[i][j].x == x2 && board[i][j].y == y2)) {
					cout << " o ";
				}
				else {
					cout << " * ";
				}
			}
			cout << endl;
		}
		en = _getch();
		if (en == 13) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (i == 0 && j == 0) {
						cout << " ";
					}
					else if (i == 0) {
						cout << " " << board[i][j].x << " ";
					}
					else if (j == 0) {
						cout << board[i][j].y;
					}
					else if ((board[i][j].x==x1&&board[i][j].y==y1)|| (board[i][j].x == x2 && board[i][j].y == y2)) {
						cout <<" " << board[i][j].x<<" ";
					}
					else {
						cout << " * ";
					}
				}
				cout << endl;
			}
		}
	}



	return 0;

}