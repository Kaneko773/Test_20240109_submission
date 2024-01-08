#include "Card.h"
#include<iostream>
using namespace std;

Card::Card() {
	_mark = 0;
	_number = 0;
}

Card::Card(int n) {
	_mark = (n % 52) % 4 + 1;
	_number = (n % 52) % 13 + 1;
}

Card::~Card() {

}

void Card::Show() {
	const char* strType[] = { "s", "h", "d", "c" };
	cout << strType[_mark - 1];
	if (_number == 1) {
		cout << "A  ";
	}
	else if (_number < 10) {
		cout << _number << "  ";
	}
	else if (_number == 10) {
		cout << _number << " ";
	}
	else {
		switch (_number)
		{
		case 11: cout << "J  "; break;
		case 12: cout << "Q  "; break;
		case 13: cout << "K  "; break;
		}
	}

}