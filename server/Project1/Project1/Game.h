#pragma once
#include <vector>
#include "Player.h"
#include "Card.h"
#include "Lobby.h"
#include <string>

class Player;
class Card;
class Lobby;

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
	Lobby * myLobby;

	std::string name;
	int maxPlayers;
	bool hasStarted;

protected:
	Card * drawCard();
	void loadDeck();
public:
	Game();
	Game(string gameName, int max);
	~Game();
	void Shuffle();
	void StartGame();
	void DealCard();
	void BurnThreeCard();
	std::string GetName();
	void AdvanceActivePlayerMarker();
	void GiveCard(Player * toPlayer);
	void ClaimPlayer(Player * newPlayer);
	void AcquireLobby(Lobby * mine);
	int GetMaxPlayerCount();
	int GetCurrentPlayerCount();
};

