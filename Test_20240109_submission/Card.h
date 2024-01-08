#pragma once
class Card
{
public:
	Card();
	Card(int n);
	virtual ~Card();

	int get_mark() const{
		return _mark;
	}
	int get_number() const{
		return _number;
	}

	void Show();

private:
	int _mark;
	int _number;
};

