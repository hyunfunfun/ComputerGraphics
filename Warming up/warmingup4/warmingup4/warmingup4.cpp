#include "Header.h"
#include "List.h"

int main() {
	List li;
	char n = 'a';
	int x, y, z;
	li.count = 0;
	li.ucount = 0;
	int c=0;
	int c1 = 0;


	while (n != 'q') {
		cout << "Ŀ�ǵ��Է�";
		::cin >> n;
		switch (n) {
		case '+':
			if (li.count < 10) {
				cout << "x y z �Է�";
				::cin >> x >> y >> z;
				li.plus(x, y, z);
				li.count++;
				cout << li.count << "  " << li.ucount << endl;
			}
			else {
				if (li.ucount != 0) {
					li.e(x, y, z);
				}
				else {
					cout << "����Ʈ �ʰ�";
				}
			}
			break;
		case '-':
			if (li.count > 0) {
				li.count--;
				li.minus();
			}
			else {
				cout << "����Ʈ �ʰ�";
			}
			break;
		case 'e':
			cout << "x y z �Է�";
			::cin >> x >> y >> z;
			li.e(x, y, z);
			break;
		case 'd':
			if (li.ucount == li.count) {
				li.count = 0;
				li.ucount = 0;
				break;
			}
			li.d();
			li.ucount++;
			break;
		case 'l':
			li.l();
			break;
		case 'c':
			li.c();
			break;
		case 'm':
			if (li.count == 0) {
				cout << "���̾���" << endl;
			}
			else {
				li.m();
			}
			break;
		case 'n':
			li.n();
			break;
		case 'a':
			if (c == 0) {
				li.a();
				c++;
			}
			else {
				li.a2();
				c = 0;
			}
			break;
		case 's':
			if (c1 == 0) {
				li.s();
				c1++;
			}
			else {
				li.s2();
				c1 = 0;
			}
			break;
		}

	}

	return 0;
}