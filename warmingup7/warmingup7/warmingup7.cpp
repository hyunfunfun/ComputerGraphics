#include "Header.h"
#include "Miro.h"


int main() {
	srand(time(NULL));
	Miro miro;
	char n='a';

	while (n != 'q') {
		cout << "��ɾ� �Է�"<<endl;
		n=_getch();
		switch (n) {
		case 13:
			system("cls");
			miro.enter();
			miro.showboard();
			break;
		case 'r':
			system("cls");
			miro.r();
			miro.showboard();
			break;
		case '+':
			system("cls");
			miro.plus();
			miro.showboard();
			break;
		case '-':
			system("cls");
			miro.minus();
			miro.showboard();
			break;
		}
	}

	return 0;
}