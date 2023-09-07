#pragma once

struct Matrix {

	int result[3][3];
	int n;
	int arr1[3][3];
	int arr2[3][3];
	void m(int arr_1[3][3], int arr_2[3][3]);
	//Çà·Ä µ¡¼À
	void a();
	void d(int arr_1[3][3], int arr_2[3][3]);
	void mul(int arr_1[3][3], int n);
	void r(int arr_1[3][3], int arr_2[3][3]);
	void t(int arr_1[3][3], int arr_2[3][3]);
	void h(int arr_1[3][3], int arr_2[3][3]);
	void s();
};