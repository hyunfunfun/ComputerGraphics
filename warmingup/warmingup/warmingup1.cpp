#include "Matrix.h"
#include "Header.h"


int main() {

	Matrix a;

	srand(time(NULL));
	char n;

	//arr1, arr2 0~2�������� ����
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			a.arr1[i][j] = rand() % 3;
			a.arr2[i][j] = rand() % 3;
		}
	}
	

	//arr1�� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a.arr1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//arr2�� ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a.arr2[i][j];
		}
		cout << endl;
	}
	n = 'a';
	while (n!='q') {
		cout << "�Է�"<<endl;
		cin >> n;
		switch (n) {
		case 'm':
			a.m(a.arr1, a.arr2);
			break;
		case 'a':
			a.a(a.arr1, a.arr2);
			break;
		case 'q':
			break;
		default:
			cout << "�ٽ��Է�" << endl;
			break;
		}
	}

	return 0;
}