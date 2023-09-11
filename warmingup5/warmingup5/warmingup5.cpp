#include "Header.h"
#include "Board.h"


int main() {
	srand(time(NULL));

	boardf board;

	//좌표 넣기
	board.inputxy();

	//대문자 넣기
	board.inputup();
	

	//대문자 섞기
	board.suffle();

	char n;
	char x1, x2;
	int y1, y2;
	char en;

	//보드 출력
	board.prtboard();

	while (1) {

		cout << "a:좌표입력 r:리셋" << endl;
		cin >> n;
		switch (n) {
		case 'a':
			cout << "1번좌표입력" << endl;
			x1 = _getch();
			y1 = _getch() - 48;


			cout << "2번좌표입력" << endl;
			x2 = _getch();
			y2 = _getch() - 48;

			system("cls");
			//좌표입력 후 o표시
			board.inputxyO(x1, y1, x2, y2);

			en = _getch();

			//엔터 눌렀을떄 나온 값 표시
			board.showen(en, x1, y1, x2, y2);

			system("cls");

			board.prtboard();
			break;
		case 'r':
			break;

		}
	return 0;

}