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
	if (count >= 10) {
		count = 9;
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
	cout << count - ucount  << endl;
}
void List::c() {
	for (int i = 0; i < 10; i++) {
		liarr[i].x = NULL;
		liarr[i].y = NULL;
		liarr[i].z = NULL;
		liarr[i].check = false;
	}
	count = 0;
	ucount = 0;
}
void List::m() {
	int max=0;
	int checki;
	for (int i = 0; i < 10; i++) {
		if (liarr[i].check == true) {
			distance = sqrt((liarr[i].x * 2) + (liarr[i].y * 2) + (liarr[i].z * 2));
			if (max < distance) {
				max = distance;
				checki = i;
			}
		}
	}
	cout << "(" << liarr[checki].x <<" ," << liarr[checki].y << " ," << liarr[checki].z << ")" << endl;
}
void List::n() {
	int max = 100000;
	int checki;
	for (int i = 0; i < 10; i++) {
		if (liarr[i].check == true) {
			distance = sqrt((liarr[i].x * 2) + (liarr[i].y * 2) + (liarr[i].z * 2));
			if (max > distance) {
				max = distance;
				checki = i;
			}
		}
	}
	cout << "(" << liarr[checki].x << " ," << liarr[checki].y << " ," << liarr[checki].z << ")" << endl;
}
void List::a() {

}
void List::s() {

}
