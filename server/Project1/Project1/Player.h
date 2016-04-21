#pragma once
class Player
{
private:
	vector<Card *> hand;
	vector<Card *>::Iterator cardIterator;
public:
	Player();
	~Player();
};

