#pragma once

#include "Player.h"

class Game
{
private:
	vector<Player *> players;
	vector<Player *>::iterator playerIterator;
	vector<Card *> deck;
	vector<Card *>::iterator deckIterator;
public:
	Game();
	~Game();
	void ShuffleDeck();
	void GiveCard(int, Player *);
};

