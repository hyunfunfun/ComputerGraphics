#include "Header.h"
#include "List.h"

int main() {
	List li;
	char n = 'a';
	int x, y, z;

	while (n != 'q') {
		cout << "커맨드입력";
		cin >> n;
		switch (n) {
		case '+':
			cout << "x y z 입력";
			cin >> x >> y >> z;
			li.plus(x, y, z);
			break;
		case '-':
			li.minus();
			break;
		case 'e':
			cout << "x y z 입력";
			cin >> x >> y >> z;
			li.e(x, y, z);
			break;
		case 'd':
			li.d();
			break;
		case 'l':
			li.l();
			break;
		case 'c':
			li.c();
			break;
		case 'm':
			li.m();
			break;
		case 'n':
			li.n();
			break;
		case 'a':
			li.a();
			break;
		case 's':
			li.s();
			break;
		}

	}

	return 0;
}