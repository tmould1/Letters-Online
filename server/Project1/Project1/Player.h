#pragma once
#include "Client.h"
#include "Card.h"
#include "Lobby.h"

class Player
{
private:
	bool inGame;
	bool myTurn;
	Client * myClient;
	Lobby * myLobby;
	std::vector<Card *> inHand;
	std::vector<Card *> discardPile;
public:
	Player();
	Player(Client* instigator);
	~Player();
	void PlayCard(int);
	void CreateGame(string name, int numPlayers);
	bool isTurn();
	string GetName();
	void ReceiveCard(Card *);
	Lobby* WhichLobby();

};

