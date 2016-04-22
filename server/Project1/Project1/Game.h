#pragma once
#include <vector>
#include "Player.h"
#include "Card.h"
#include <string>

class Game
{
private:
	std::vector<Player *> players;
	std::vector<Player *>::iterator playerIterator;
	std::vector<Player *>::iterator ActivePlayerIterator;
	Card * actualCards[16];
	std::vector<Card *> deck;
	std::vector<Card *>::iterator deckIterator;
	std::vector<Card *> pickUpDeck;     //  Only give the illusion of dealing a card.  Keep it in your pickUpDeck
	std::vector<Card *> burnPile;
	Card * faceDownCard;

	
	std::string name;
	bool hasStarted;

protected:
	Card * drawCard();
public:
	Game();
	~Game();
	void Shuffle();
	void StartGame();
	void DealCard();
	void BurnThreeCard();
	string GetName();
	void AdvanceActivePlayerMarker();
	void GiveCard(Player * toPlayer);
};

