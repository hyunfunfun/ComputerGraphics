#include "Header.h"
#include "string.h"

void fstring::d(){
	for (int i = 0; i < 10; i++) {
		int len = str[i].length();
		for (int j = len; j > 0; j--) {
			for (int k = 0; k < len; k++) {
				str2[i][k] = str[i][j - 1];
				j--;
			}
		}
		str[i] = str2[i];
		
		cout <<str[i]<< endl;
	}
}
void fstring::e()
{
	for (int i = 0; i < 10; i++) {
		int len = str[i].length();
		for (int j = 1; j <= len;j++) {
			if (j%3==0) {
				str[i].insert(j,"@@");
				len += 2;
				
			}
		}
		cout << str[i]<<endl;
	}
}
void fstring::f()
{

}
void fstring::g()
{

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