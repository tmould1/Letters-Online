#pragma once
#include "Client.h"
#include "Card.h"

class Player
{
private:
	bool inGame;
	bool myTurn;
	Client * myClient;
	std::vector<Card *> inHand;
	ServerManager * sm;
public:
	Player();
	Player(Client* instigator);
	~Player();
	void PlayCard(Card *);
	void CreateGame();
	bool isTurn();
	string GetName();
	void ReceiveCard(Card *);
	void acquireServerManager();
};

