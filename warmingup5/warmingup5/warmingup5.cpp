#include "Header.h"

struct board {
	char x;
	int y;
	char data;
};

int main() {
	srand(time(NULL));
	board board[5][5];

	//좌표 넣기
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
	}

	//대문자 넣기
	int ch = 65;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			board[i][j].data = ch;
			if (j % 2 == 0) {
				ch++;
			}
		}
	}
	//대문자 섞기
	int rn1;
	int rn2;
	char temp;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			rn1 = rand() % 4 + 1;
			rn2 = rand() % 4 + 1;

			temp = board[i][j].data;
			board[i][j].data = board[rn1][rn2].data;
			board[rn1][rn2].data;
		}
	}

	char n;
	char x1, x2;
	int y1, y2;
	char en;


	//보드 출력
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
		cout << "1번좌표입력"<<endl;
		x1 = _getch();
		y1 = _getch()-48;


		cout << "2번좌표입력"<<endl;
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
						cout <<" " << board[i][j].data<<" ";
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