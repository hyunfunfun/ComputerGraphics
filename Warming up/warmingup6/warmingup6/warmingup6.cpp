#include "Header.h"
#include "MoveOb.h"

int main() {
	MoveOb mo;
	char n;
	int x1, y1;
	int x2, y2;


	mo.showboard();
	cout << "x1,y1 입력";
	cin >> mo.boardx1 >> mo.boardy1;
	cout << "x2,y2 입력";
	cin >> mo.boardx2 >> mo.boardy2;
	mo.changedata();
	
	while (1) {
		system("cls");
		mo.showboard();
		
		cout << "명령어 입력" << endl;
		cin >> n;
		switch (n) {
		case 'x':
			system("cls");
			mo.x();
			break;
		case 'X':
			system("cls");
			mo.X();
			break;
		case 'y':
			system("cls");
			mo.y();
			break;
		case 'Y':
			system("cls");
			mo.Y();
			break;
		case 's':
			system("cls");
			mo.s();
			break;
		case 'S':
			system("cls");
			mo.S();
			break;
		case 'i':
			system("cls");
			mo.i();
			break;
		case 'j':
			system("cls");
			mo.j();
			break;
		case 'k':
			system("cls");
			mo.k();
			break;
		case 'l':
			system("cls");
			mo.l();
			break;
		case 'R':
			system("cls");
			mo.R();
			break;
		}
	}

	return 0;
}