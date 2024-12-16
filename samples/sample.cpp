
#include <iostream>
#include <string>
#include "translator.h"
using namespace std;


int main() {
	string str;
	cout << "input an arithmetic expression:  " ;
	cin >> str;
	translator t(str);
	cout << endl << "answer: " << t.get_result() << endl;
}
