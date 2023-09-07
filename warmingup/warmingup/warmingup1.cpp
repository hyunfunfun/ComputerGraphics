#include "Matrix.h"
#include "Header.h"


int main() {

	Matrix a;

	srand(time(NULL));
	char n;

	//arr1, arr2 0~2랜덤숫자 적용
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			a.arr1[i][j] = rand() % 3;
			a.arr2[i][j] = rand() % 3;
		}
	}
	

	//arr1의 행렬
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a.arr1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//arr2의 행렬
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a.arr2[i][j];
		}
		cout << endl;
	}
	n = 'a';
	while (n!='q') {
		cout << "입력"<<endl;
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
			cout << "다시입력" << endl;
			break;
		}
	}

	return 0;
}