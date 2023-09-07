#include "Matrix.h"
#include "Header.h"

//Çà·Ä °ö¼À
void Matrix::m(int arr_1[3][3], int arr_2[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				result[i][j] += arr_1[i][k] * arr_2[k][j];
			}
			
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result[i][j];
		}
		cout << endl;
	}
};
//Çà·Ä µ¡¼À
void Matrix::a(int arr_1[3][3], int arr_2[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = arr_1[i][j] + arr_2[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result[i][j];
		}
		cout << endl;
	}
};
void Matrix::d() {

};
void Matrix::r(){};
void Matrix::t(){};
void Matrix::h(){};
void Matrix::s(){};
void Matrix::q(){};