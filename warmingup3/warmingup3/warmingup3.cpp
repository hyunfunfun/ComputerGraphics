#include "Header.h"
#include "string.h"

int main() {
	char n='a';
	int i = 0;
	fstring fs;
	ifstream file;
	file.open("data.txt");

	string str;
	string str2;

	while (!file.eof()) {
		getline(file, str);
		fs.str[i] = str;
		stringstream s(str);
		cout << fs.str[i] << endl;
		i++;
	}
	

	while (n!='q') {
		cout << "커맨드입력"<<endl;
		cin >> n;
		switch (n){
		case 'd':
			fs.d();
			break;
		case 'e':
			fs.e();
			break;
		case 'f':
			fs.f();
			break;
		case 'g':
			fs.g();
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