#include "Header.h"
#include "Board.h"


int main() {
	srand(time(NULL));

	boardf board;

	//��ǥ �ֱ�
	board.inputxy();

	//�빮�� �ֱ�
	board.inputup();
	

	//�빮�� ����
	board.suffle();

	char n;
	char x1, x2;
	int y1, y2;
	char en;

	//���� ���
	board.prtboard();

	while (1) {

		cout << "a:��ǥ�Է� r:����" << endl;
		cin >> n;
		switch (n) {
		case 'a':
			cout << "1����ǥ�Է�" << endl;
			x1 = _getch();
			y1 = _getch() - 48;


			cout << "2����ǥ�Է�" << endl;
			x2 = _getch();
			y2 = _getch() - 48;

			system("cls");
			//��ǥ�Է� �� oǥ��
			board.inputxyO(x1, y1, x2, y2);

			en = _getch();

			//���� �������� ���� �� ǥ��
			board.showen(en, x1, y1, x2, y2);

			system("cls");

			board.prtboard();
			break;
		case 'r':
			break;

		}
	return 0;

}