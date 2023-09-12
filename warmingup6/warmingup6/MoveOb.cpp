#include "Header.h"
#include "MoveOb.h"

void temp(int a, int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
void MoveOb::showboard() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			cout << " " << ob[i][j].data << " ";
		}
		cout << endl;
	}
}
void MoveOb::changedata() {
	
	if (boardx1 > boardx2) {
		temp(boardx1, boardx2);
	}
	if (boardy1 > boardy2) {
		temp(boardy1, boardy2);
	}
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if ((overx2>=0) || (overx1<30) (overy1 <= i && overy2 >= i)) {//¼öÁ¤
				ob[i][j].data = '0';
			}
			else if ((boardx1 <= j && boardx2 >= j) && (boardy1 <= i && boardy2 >= i)) {
				ob[i][j].data = '0';
			}
			else {
				ob[i][j].data = '.';
			}
		}
	}
}
void MoveOb::x() {
	boardx1++;
	boardx2++;
	if (boardx2 >= 30) {
		overx1 = 0;
		overx2 = boardx2 - 30;
		overy1 = boardy1;
		overy2 = boardy2;
		if (boardx1 >= 30) {
			boardx1 = overx1;
			boardx2 = overx2;
			overx1 = -1;
			overx2 = -1;
		}
	}
	changedata();
}
void MoveOb::X() {
	boardx1--;
	boardx2--;
	if (boardx1 <= -1) {
		overx1 = boardx1+30;
		overx2 = 29;
		overy1 = boardy1;
		overy2 = boardy2;
		if (boardx2 <= -1) {
			boardx1 = overx1;
			boardx2 = overx2;
			overx1 = -1;
			overx2 = -1;
		}
	}
	changedata();
}
void MoveOb::y() {
	boardy1++;
	boardy2++;
	if (boardy2 >= 30) {
		overy1 = 0;
		overy2 = boardy2 - 30;
		overx1 = boardx1;
		overx2 = boardx2;
		if (boardy1 >= 30) {
			boardy1 = overy1;
			boardy2 = overy2;
			overy1 = -1;
			overy2 = -1;
		}
	}
	changedata();
}
void MoveOb::Y() {
	boardy1--;
	boardy2--;
	if (boardy1 <= -1) {
		overy1 = boardy1 + 30;
		overy2 = 29;
		overx1 = boardx1;
		overx2 = boardx2;
		if (boardy2 <= -1) {
			boardy1 = overy1;
			boardy2 = overy2;
			overy1 = -1;
			overy2 = -1;
		}
	}
	changedata();
}
void MoveOb::s() {
	if (overx1 == -1 && overx2 == -1 && overy1 == -1 && overy2 == -1) {
		boardx2--;
		boardy2--;
	}
	changedata();
}
void MoveOb::S() {

}
void MoveOb::i() {

}
void MoveOb::j() {

}
void MoveOb::k() {

}
void MoveOb::l() {

}
void MoveOb::R() {

}