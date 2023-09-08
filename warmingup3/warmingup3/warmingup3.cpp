#include "Header.h"
#include "string.h"

int main() {
	fstring fs;
	ifstream file;
	file.open("data.txt");
	string str;
	string str2;


	int i = 0;
	while (!file.eof()) {
		getline(file, str);
		fs.str[i] = str;
		cout << fs.str[i] << endl;
		i++;
	}


	char n = 'a';
	fs.count = 0;
	char a, b;
	while (n!='q') {
		cout << "커맨드입력"<<endl;
		cin >> n;
		switch (n){
		case 'd':
			fs.d();
			break;
		case 'e':
			if (fs.count == 0) {
				fs.e();
				fs.count = 1;
			}
			else {
				fs.e2();
				fs.count = 0;
			}
			break;
		case 'f':
			fs.f();
			break;
		case 'g':
			cout << "바꿀문자 : ";
			cin >> a;
			cout << "새로입력할 문자 : ";
			cin >> b;
			fs.g(a,b);
			break;
		case 'h':
			fs.h();
			break;
		case '+':
			fs.plus();
			break;
		case '-':
			fs.minus();
			break;
		default:
			cout << "다시입력" << endl;
			break;
		}

	}

	file.close();
	return 0;
}