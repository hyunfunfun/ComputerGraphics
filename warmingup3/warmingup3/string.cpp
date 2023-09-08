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

}
void fstring::plus()
{

}
void fstring::minus()
{

}