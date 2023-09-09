#include "Header.h"
#include "List.h"

void List::plus(int x_, int y_, int z_) {
	liarr[count].x = x_;
	liarr[count].y = y_;
	liarr[count].z = z_;
	liarr[count].check = true;
	for (int i = 9; i >= 0; i--) {
		if (liarr[i].check == false) {
			cout << i << " : " << "-" << " " << "-" << " " << "-" << " " << endl;
		}
		else {
			cout << i << " : " << liarr[i].x << " " << liarr[i].y << " " << liarr[i].z << " " << endl;
		}
		
	}
}
void List::minus(){
	liarr[count].x = NULL;
	liarr[count].y = NULL;
	liarr[count].z = NULL;
	liarr[count].check = false;
	for (int i = 9; i >= 0; i--) {
		if (liarr[i].check == false) {
			cout << i << " : " << "-" << " " << "-" << " " << "-" << " " << endl;
		}
		else {
			cout << i << " : " << liarr[i].x << " " << liarr[i].y << " " << liarr[i].z << " " << endl;
		}

	}
}
void List::e(int x_, int y_, int z_) {
	if (ucount == 0) {
		for (int i = 9; i >= 0; i--) {
			liarr[i] = liarr[i - 1];
		}
		count++;
	}
	else {
		ucount--;
	}
	liarr[ucount].x = x_;
	liarr[ucount].y = y_;
	liarr[ucount].z = z_;
	liarr[ucount].check = true;
	for (int i = 9; i >= 0; i--) {
		if (liarr[i].check == false) {
			cout << i << " : " << "-" << " " << "-" << " " << "-" << " " << endl;
		}
		else {
			cout << i << " : " << liarr[i].x << " " << liarr[i].y << " " << liarr[i].z << " " << endl;
		}

	}
}
void List::d() {
	liarr[ucount].x = NULL;
	liarr[ucount].y = NULL;
	liarr[ucount].z = NULL;
	liarr[ucount].check = false;
	for (int i = 9; i >= 0; i--) {
		if (liarr[i].check == false) {
			cout << i << " : " << "-" << " " << "-" << " " << "-" << " " << endl;
		}
		else {
			cout << i << " : " << liarr[i].x << " " << liarr[i].y << " " << liarr[i].z << " " << endl;
		}

	}
}
void List::l() {

}
void List::c() {

}
void List::m() {

}
void List::n() {

}
void List::a() {

}
void List::s() {

}
