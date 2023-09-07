#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"

using namespace std;

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

	cin >> n;
	switch (n) {
	case 'a':
		a.a(a.arr1,a.arr2);
		break;
	}

	return 0;
}