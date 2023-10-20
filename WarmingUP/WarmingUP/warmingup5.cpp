#include "Header.h"

struct board {
	char x;
	int y;
	char data;
	bool check=false;
};

int main() {
	srand(time(NULL));
	board board[5][5];
	int gamecount = 6;
	int score = 0;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//��ǥ �ֱ�
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

	//�빮�� �ֱ�
	int ch = 65;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			board[i][j].data = ch;
			if (j % 2 == 0) {
				ch++;
			}
		}
	}

	//�빮�� ����
	int rn1;
	int rn2;
	char temp;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			rn1 = rand() % 4 + 1;
			rn2 = rand() % 4 + 1;

			temp = board[i][j].data;
			board[i][j].data = board[rn1][rn2].data;
			board[rn1][rn2].data = temp;
		}
	}

	char n;
	char x1, x2;
	int y1, y2;
	char en;

	int i1 = 0, j1 = 0;
	int i2 = 0, j2 = 0;

	while (1) {

		if (gamecount == 0) {
			cout << "���� : " << score << endl;
			break;
		}
		system("cls");
		//���� ���
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
				else if (board[i][j].check == true) {
					cout << " " << board[i][j].data << " ";
				}
				else {
					cout << " * ";
				}
			}
			cout << endl;
		}
		cout << "������ȸ" <<gamecount<<endl<< "a:��ǥ�Է� b:����Ű �Է� r:����" << endl;
		cin >> n;
		switch (n) {
		case 'a':
			gamecount--;
			cout << "1����ǥ�Է�" << endl;
			x1 = _getch();
			y1 = _getch() - 48;


			cout << "2����ǥ�Է�" << endl;
			x2 = _getch();
			y2 = _getch() - 48;

			system("cls");
			//��ǥ�Է� �� oǥ��
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
					else if (board[i][j].check == true) {
						cout << " " << board[i][j].data << " ";
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

			//���� �������� ���� �� ǥ��
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
						else if (board[i][j].check == true) {
							cout << " " << board[i][j].data << " ";
						}
						else if (board[i][j].x == x1 && board[i][j].y == y1) {
							SetConsoleTextAttribute(handle, board[i][j].data - 65);
							cout << " " << board[i][j].data << " ";
							SetConsoleTextAttribute(handle, 7);
							i1 = i;
							j1 = j;
						}
						else if (board[i][j].x == x2 && board[i][j].y == y2) {
							SetConsoleTextAttribute(handle, board[i][j].data-65);
							cout << " " << board[i][j].data << " ";
							SetConsoleTextAttribute(handle, 7);
							i2 = i;
							j2 = j;
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
			}
			//�ٸ� Ű�� �������� 
			else {
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
						else if (board[i][j].check == true) {
							cout << board[i][j].data;
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
			}

			//���� ���� ������ ���ǥ��
			if (board[i1][j1].data == board[i2][j2].data) {
				board[i1][j1].check = true;
				board[i2][j2].check = true;
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
						else if (board[i][j].check == true) {
							SetConsoleTextAttribute(handle, board[i][j].data - 65);
							cout << " " << board[i][j].data << " ";
							SetConsoleTextAttribute(handle, 7);
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
				score++;
			}
			//���� ���� �ٸ��� 
			else {
				Sleep(2000);
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
						else if (board[i][j].check == true) {
							cout << " " << board[i][j].data << " ";
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
			}

			system("cls");

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
					else if (board[i][j].check == true) {
						cout << " " << board[i][j].data << " ";
					}
					else {
						cout << " * ";
					}
				}
				cout << endl;
			}
			break;
		case 'r':
			for (int i = 1; i < 5; i++) {
				for (int j = 1; j < 5; j++) {
					board[i][j].check = false;
					rn1 = rand() % 4 + 1;
					rn2 = rand() % 4 + 1;
					temp = board[i][j].data;
					board[i][j].data = board[rn1][rn2].data;
					board[rn1][rn2].data = temp;
				}
			}
			gamecount = 6;
			score = 0;
			break;
		case 'b':
			gamecount--;
			int input;
			int keyx = 1;
			int keyy = 1;
			int count = 0;

			while (1) {
				//�������
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
						else if ((keyy == i && keyx == j) || i1 == i && j1 == j) {
							cout << " o ";
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
				input = _getch();

				if (input == 72) {
					if (keyy == 1) {
						keyy = 1;
					}
					else {
						keyy -= 1;
					}
				}
				else if (input == 80) {
					if (keyy == 4) {
						keyy = 4;
					}
					else {
						keyy += 1;
					}
				}
				else if (input == 77) {
					if (keyx == 4) {
						keyx = 4;
					}
					else {
						keyx += 1;
					}
				}
				else if (input == 75) {
					if (keyx == 1) {
						keyx = 1;
					}
					else {
						keyx -= 1;
					}
				}
				else if (input == 13) {
					if (count == 1) {
						i2 = keyy;
						j2 = keyx;
						count = 0;
						break;
					}
					else {
						i1 = keyy;
						j1 = keyx;
						count++;
					}
				}
				system("cls");
				

			}
			//���� �������� ���� �� ǥ��
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
					else if (board[i][j].check == true) {
						SetConsoleTextAttribute(handle, board[i][j].data - 65);
						cout << " " << board[i][j].data << " ";
						SetConsoleTextAttribute(handle, 7);
					}
					else if ((i1 == i && j1 == j) || (i2 == i && j2 == j)) {
						SetConsoleTextAttribute(handle, board[i][j].data - 65);
						cout << " " << board[i][j].data << " ";
						SetConsoleTextAttribute(handle, 7);

					}
					else {
						cout << " * ";
					}
				}
				cout << endl;
			}

			//���� ���� ������ ���ǥ��
			if (board[i1][j1].data == board[i2][j2].data) {
				board[i1][j1].check = true;
				board[i2][j2].check = true;
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
						else if (board[i][j].check == true) {
							SetConsoleTextAttribute(handle, board[i][j].data - 65);
							cout << " " << board[i][j].data << " ";
							SetConsoleTextAttribute(handle, 7);
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
				score++;
			}
			//���� ���� �ٸ��� 
			else {
				Sleep(2000);
				i1 = 0; j1 = 0;
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
						else if (board[i][j].check == true) {
							cout << " " << board[i][j].data << " ";
						}
						else {
							cout << " * ";
						}
					}
					cout << endl;
				}
			}
			break;
		}
	}


	return 0;
}