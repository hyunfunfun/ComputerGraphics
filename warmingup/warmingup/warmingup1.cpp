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
			a.a();
			break;
		case 'd':
			a.d(a.arr1, a.arr2);
		case 'q':
			break;
		case '1':
			a.mul(a.arr1, (int)n-48);
			break;
		case '2':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '3':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '4':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '5':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '6':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '7':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '8':
			a.mul(a.arr1, (int)n - 48);
			break;
		case '9':
			a.mul(a.arr1, (int)n - 48);
			break;
		case 'r':
			a.r(a.arr1, a.arr2);
			break;
		case 't':
			a.t(a.arr1, a.arr2);
			break;
		case 'h':
			a.h(a.arr1,a.arr2);
			break;
		case 's':
			a.s();
			break;
		default:
			cout << "다시입력" << endl;
			break;
		}
	}

	return 0;
}