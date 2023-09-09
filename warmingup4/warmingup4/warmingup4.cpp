#include "Header.h"
#include "List.h"

int main() {
	List li;
	char n = 'a';
	int x, y, z;
	li.count = 0;
	li.ucount = 0;


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
				cout << "����Ʈ �ʰ�";
			}
			break;
		case '-':
			if (li.count > 0) {
				li.count--;
				li.minus();
				cout << li.count << "  " << li.ucount << endl;
			}
			else {
				cout << "����Ʈ �ʰ�";
			}
			break;
		case 'e':
			cout << "x y z �Է�";
			::cin >> x >> y >> z;
			li.e(x, y, z);
			cout << li.count << "  " << li.ucount << endl;
			break;
		case 'd':
			if (li.ucount == li.count) {
				li.count = 0;
				li.ucount = 0;
				break;
			}
			li.d();
			li.ucount++;
			cout << li.count << "  " << li.ucount << endl;
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
			li.a();
			break;
		case 's':
			li.s();
			break;
		}

	}

	return 0;
}