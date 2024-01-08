#pragma once

#include "Card.h"

class Shoe
{
public:
	Shoe();
	virtual ~Shoe();

	void set_shoe(int deckNum);
	Card takeCard();

	//デバッグ用
	void Show_shoe();

	int get_remCardNum() const{
		return _remCardNum;
	}

private:
	void _shuffle();
	Card* _shoe;
	int _remCardNum;
};

