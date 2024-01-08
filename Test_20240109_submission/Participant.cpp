#define _CRT_SECURE_NO_WARNINGS
#include "Participant.h"
#include<iostream>
#include<cstring>
using namespace std;

Participant::Participant(const char* name)
{
	_pName = new char[strlen(name) + 1];
	strcpy(_pName, name);
	_playerOrNot = false;
	_pHand = nullptr;
	_handNum = 0;
}

Participant::~Participant()
{
	if (_pName != nullptr) {
		delete[] _pName;
		_pName = nullptr;
	}
}

void Participant::change_playerOrNot()
{
	_playerOrNot ? _playerOrNot = false : _playerOrNot = true;
}

void Participant::set_pName(const char* pName)
{
	if (_pName != nullptr) {
		delete[] _pName;
		_pName = new char[strlen(pName) + 1];
		strcpy(_pName, pName);
	}
}

Card* Participant::get_pHand(int n) const
{
	if (n > _handNum) {
		cout << "get_pHandでエラー" << endl;
		return nullptr;
	}
	return &_pHand[n - 1];
}

void Participant::reset_pHand()
{
	if (_pName != nullptr) {
		delete[] _pHand;
		_pHand = nullptr;
	}
	_handNum = 0;
}

void Participant::takeCard(Shoe* shoe)
{
	Card* viaPtr = _pHand;
	_pHand = new Card[_handNum + 1];
	//エラー処理
	if (_pHand == nullptr) {
		delete[] viaPtr;
		viaPtr = nullptr;
		cout << "Participant::takeCard()でエラーが発生しました" << endl;
		return;
	}

	for (int i = 0; i < _handNum; ++i) {
		_pHand[i] = viaPtr[i];
	}
	++_handNum;
	_pHand[_handNum - 1] = shoe->takeCard();
	if (viaPtr != nullptr) {
		delete[] viaPtr;
		viaPtr = nullptr;
	}
}

int Participant::BCcalcScore()
{
	if (_handNum <= 0)return 0;

	int score = 0;
	for (int i = 0; i < _handNum; ++i) {
		if (_pHand[i].get_number() <= 9) {
			score += _pHand[i].get_number();
		}
	}

	score = (score % 10);

	return score;
}
