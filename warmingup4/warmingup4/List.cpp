#include "Header.h"
#include "List.h"

void List::plus(int x_, int y_, int z_) {
	liarr[count].x = x_;
	liarr[count].y = y_;
	liarr[count].z = z_;
	for (int i = 9; i >= 0; i--) {
		
		cout << i << " : " << liarr[i].x << " " << liarr[i].y << " " << liarr[i].z << " " << endl;
	}
}
void List::minus(){
	liarr[count].x = NULL;
	liarr[count].y = NULL;
	liarr[count].z = NULL;
	for (int i = 9; i >= 0; i--) {

		cout << i << " : " << liarr[i].x << " " << liarr[i].y << " " << liarr[i].z << " " << endl;
	}
}
void List::e(int x_, int y_, int z_) {

}
void List::d() {

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
