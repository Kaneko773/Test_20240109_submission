#include <iostream>
#include "Shoe.h"
using namespace std;

Shoe::Shoe() {
	_shoe = nullptr;
	_remCardNum = 0;
}

Shoe::~Shoe() {
	if (_shoe != nullptr) {
		delete[] _shoe;
		_shoe = nullptr;
	}
}

void Shoe::set_shoe(int deckNum) {
	if (_shoe != nullptr) {
		delete[] _shoe;
		_shoe = nullptr;
	}
	_remCardNum = deckNum * 52;
	_shoe = new Card[_remCardNum];
	_shuffle();
}

Card Shoe::takeCard() {
	Card returnCard;
	Card nonCard;//エラー用

	//エラーチェック
	if (_shoe == nullptr) {
		cout << "シューにカードが入っていません:エラー" << endl;
		return nonCard;
	}
	if (_remCardNum <= 0) {
		cout << "シューにカードが入っていません" << endl;
		return nonCard;
	}

	returnCard = _shoe[_remCardNum - 1];

	//シューから１枚減らす
	--_remCardNum;
	if (_remCardNum <= 0) {
		cout << "シュー内のカードが無くなりました" << endl;
		return returnCard;
	}
	Card* a = _shoe;
	if (a == nullptr) {
		cout << "エラーが起こりました" << endl;
		return nonCard;
	}
	_shoe = new Card[_remCardNum];
	if (_shoe == nullptr) {
		cout << "エラーが起こりました" << endl;
		return nonCard;
	}
	for (int i = 0; i < _remCardNum; ++i) {
		_shoe[i] = a[i];
	}
	if (a != nullptr) {
		delete[] a;
		a = nullptr;
	}
	else {
		cout << "エラー" << endl;
	}

	return returnCard;
}

void Shoe::_shuffle() {
	int* shuffle = new int[_remCardNum];
	if (shuffle == nullptr) {
		return;
	}

	//シャッフル
	for (int i = 0; i < _remCardNum; ++i) {
		shuffle[i] = i;
	}
	for (int i = _remCardNum; i > 1; --i) {
		int a = i - 1;
		int b = rand() % i;
		swap(shuffle[a], shuffle[b]);
	}

	//生成
	for (int i = 0; i < _remCardNum; ++i) {
		Card card(shuffle[i]);
		_shoe[i] = card;
	}

	if (shuffle != nullptr) {
		delete[] shuffle;
		shuffle = nullptr;
	}
}