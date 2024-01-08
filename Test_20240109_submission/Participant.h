#pragma once
#include "Card.h"
#include "Shoe.h"
#include<iostream>
using namespace std;
class Participant
{
public:
	Participant(const char* pname);
	virtual ~Participant();

	void change_playerOrNot();
	bool get_playerOrNot() const {
		return (_playerOrNot ? true : false);
	}

	char* get_pName() const{
		return _pName;
	}
	void set_pName(const char* pName);

	//n‚Í_handNum–‡–Ú‚ð“ü—Í
	Card* get_pHand(int n) const;

	void reset_pHand();

	int get_handNum() const{
		return _handNum;
	}

	void takeCard(Shoe* shoe);

	int BCcalcScore();

private:
	bool _playerOrNot;
	char* _pName;
	Card* _pHand;
	int _handNum;
};

