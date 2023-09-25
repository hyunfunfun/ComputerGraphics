#include "Header.h"

int main() {

	ifstream file;
	file.open("data.txt");
	int wordcount=0;
	int numcount=0;
	int Ccount=0;

	string str;
	string str2;
	while (!file.eof()) {
		getline(file, str);
		stringstream s(str);
		
		while (s >> str2) {
			cout << str2<<" ";
			if (48<=str2[0] && str2[0] <= 57) {
				numcount++;
			}
			else {
				if (65 <= str2[0] && str2[0] <= 90) {
					Ccount++;
				}
				wordcount++;
			}
		}
		cout << endl;
	}
	cout << "wordcount" << wordcount << endl<<"numbercount"<<numcount<<endl<<"Capital word"<<Ccount<<endl;

	file.close();
	return 0;
}