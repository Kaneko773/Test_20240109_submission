#pragma once
#include "common.h"
#include "Card.h"

class Shoe
{
public:
	Shoe();
	virtual ~Shoe();

	void set_shoe(int deckNum);
	Card takeCard();

	int get_remCardNum() const{
		return _remCardNum;
	}

	void set_mode(GameMode mode);

private:
	void _shuffle();
	Card* _shoe;
	int _remCardNum;
	GameMode _mode;
};

