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
			miro.enter();
			miro.showboard();
			break;
		case 'r':
			miro.r();
			break;
		case '+':
			miro.plus();
			break;
		case '-':
			miro.minus();
			break;
		}
	}

	return 0;
}