#include "Header.h"
#include "string.h"

void fstring::d(){
	for (int i = 0; i < 10; i++) {
		int len = str[i].length();
		str2[i] = str[i];
		for (int j = 0; j <len; j++) {
			str2[i][j] = str[i][len - j-1];
		}
		str[i] = str2[i];
		
		cout <<str[i]<< endl;
	}
}
void fstring::e()
{
	for (int i = 0; i < 10; i++) {
		int len = str[i].length();
		for (int j = 3; j < len+1; j+=5) {
			str[i].insert(j, "@@");
			len += 2;
		}
		cout << str[i] << endl;
	}
}
void fstring::e2()
{
	for (int i = 0; i < 10; i++) {
		str[i].erase(remove(str[i].begin(), str[i].end(),'@'), str[i].end());
		//remove로 @삭제 후, size가 그대로인 str[i]의 뒤에 있는 쓰레기값을 erase로 삭제
		cout << str[i] << endl;
	}
}
void fstring::f()
{
	for (int i = 0; i < 10; i++) {
		stringstream s(str[i]);
		string astr;
		while (s >> astr) {
			reverse(astr.begin(), astr.end());
			str2[i].append(astr);
			str2[i].append(" ");
		}
		str2[i].pop_back();
		str[i] = str2[i];
		str2[i] = "";
		cout << str[i] << endl;
	}
}
void fstring::g(char a, char b)
{
	for (int i = 0; i < 10; i++) {
		replace(str[i].begin(), str[i].end(), a, b);
		cout << str[i] << endl;
	}
}
void fstring::h()
{
	for (int i = 0; i < 10; i++) {
		int len = str[i].length();
		char* a = new char[len];
		for (int k = 0; k < len; k++) {
			a[k] = NULL;
		}
		str2[i] = str[i];
		for (int j = 0; j < len / 2; j++) {
			if (str2[i][j] == str[i][len - j - 1]) {
				a[j] = str2[i][j];
			}
			else {
				break;
			}
		}
		if (a[0] == NULL) {
			cout << str2[i] << " : " << "0" << endl;
		}
		else {
			cout << str2[i] << " : " << a << endl;
		}
	}
}
void fstring::plus()
{
	bool ch = true;
	for (int i = 0; i < 10; i++) {
		stringstream s(str[i]);
		string astr;
		int num;
		while (s >> astr) {
			for (int i = 0; i < astr.length(); i++) {
				if (48 <= (int)astr[i] && 57 >= (int)astr[i]) {
					ch = true;
				}
				else {
					ch = false;
					break;
				}
			}
			if (ch==true) {
				stringstream ss;
				stringstream sss;
				ss << astr;
				ss >> num;
				num++;
				sss << num;
				sss >> astr;
			}
			str2[i].append(astr);
			str2[i].append(" ");
		}
		str2[i].pop_back();
		str[i] = str2[i];
		str2[i] = "";
		cout << str[i] << endl;
	}
}
void fstring::minus()
{
	bool ch = true;
	for (int i = 0; i < 10; i++) {
		stringstream s(str[i]);
		string astr;
		int num;
		while (s >> astr) {
			for (int i = 0; i < astr.length(); i++) {
				if (48 <= (int)astr[i] && 57 >= (int)astr[i]) {
					ch = true;
				}
				else {
					ch = false;
					break;
				}
			}
			if (ch == true) {
				stringstream ss;
				stringstream sss;
				ss << astr;
				ss >> num;
				num--;
				sss << num;
				sss >> astr;
			}
			str2[i].append(astr);
			str2[i].append(" ");
		}
		str2[i].pop_back();
		str[i] = str2[i];
		str2[i] = "";
		cout << str[i] << endl;
	}
}