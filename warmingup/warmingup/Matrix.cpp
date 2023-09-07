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
void Matrix::a() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = arr1[i][j] + arr2[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result[i][j];
		}
		cout << endl;
	}
};
void Matrix::d(int arr_1[3][3], int arr_2[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = arr_1[i][j] - arr_2[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result[i][j];
		}
		cout << endl;
	}
};
void Matrix::mul(int arr_1[3][3], int n) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = arr_1[i][j] * n;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << result[i][j];
		}
		cout << endl;
	}
}
void Matrix::r(int arr_1[3][3], int arr_2[3][3]){
	int result1 = arr_1[0][0] * (arr_1[1][1] * arr_1[2][2] - arr_1[1][2] * arr_1[2][1]) -
		arr_1[0][1] * (arr_1[1][0] * arr_1[2][2] - arr_1[1][2] * arr_1[2][0]) +
		arr_1[0][2] * (arr_1[1][0] * arr_1[2][1] - arr_1[1][1] * arr_1[2][0]);
	cout << result1 << endl;
	int result2 = arr_2[0][0] * (arr_2[1][1] * arr_2[2][2] - arr_2[1][2] * arr_2[2][1]) -
		arr_2[0][1] * (arr_2[1][0] * arr_2[2][2] - arr_2[1][2] * arr_2[2][0]) +
		arr_2[0][2] * (arr_2[1][0] * arr_2[2][1] - arr_2[1][1] * arr_2[2][0]);
	cout << result2 << endl;
};
void Matrix::t(int arr_1[3][3], int arr_2[3][3]){
	int mat1[3][3];
	int mat2[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat1[j][i] = arr_1[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << mat1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat2[j][i] = arr_2[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << mat2[i][j];
		}
		cout << endl;
	}
	r(mat1, mat2);
};
void Matrix::h(int arr_1[3][3], int arr_2[3][3]){
	int newarr1[4][4];
	int newarr2[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 3 && j == 3) {
				newarr1[i][j] = 1;
				newarr2[i][j] = 1;
			}
			else if (i == 3 || j == 3) {
				newarr1[i][j] = 0;
				newarr2[i][j] = 0;
			}
			else {
				newarr1[i][j] = arr_1[i][j];
				newarr2[i][j] = arr_2[i][j];
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << newarr1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << newarr2[i][j];
		}
		cout << endl;
	}
	int result1 = arr_1[0][0] * (arr_1[1][1] * arr_1[2][2] - arr_1[1][2] * arr_1[2][1]) -
		arr_1[1][0] * (arr_1[0][1] * arr_1[2][2] - arr_1[0][2] * arr_1[2][1]) +
		arr_1[2][0] * (arr_1[0][1] * arr_1[1][2] - arr_1[0][2] * arr_1[1][1]);
	cout << result1 << endl;
	int result2 = arr_2[0][0] * (arr_2[1][1] * arr_2[2][2] - arr_2[1][2] * arr_2[2][1]) -
		arr_2[1][0] * (arr_2[0][1] * arr_2[2][2] - arr_2[0][2] * arr_2[2][1]) +
		arr_2[2][0] * (arr_2[0][1] * arr_2[1][2] - arr_2[0][2] * arr_2[1][1]);
	cout << result2 << endl;

};
void Matrix::s(){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			arr1[i][j] = rand() % 3;
			arr2[i][j] = rand() % 3;
		}
	}
	//arr1ÀÇ Çà·Ä
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	//arr2ÀÇ Çà·Ä
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr2[i][j];
		}
		cout << endl;
	}
};