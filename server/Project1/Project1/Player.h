#pragma once
#include "Card.h"
#include "Lobby.h"
#include "Client.h"
#include <string>

class Client;
class Lobby;
class Card;

class Player
{
private:
	bool inGame;
	bool isOut;
	bool myTurn;
	Client * myClient;
	Game * myGame;
	Lobby * myLobby;
	std::vector<Card *> inHand;
	std::vector<Card *> discardPile;
public:
	Player();
	Player(Client* instigator);
	~Player();
	void PlayCard(int);
	void CreateGame(std::string name, int numPlayers);
	bool isTurn();
	std::string GetName();
	void ReceiveCard(Card *);
	void DiscardCard(Card *);
	bool HasCard(Card *);
	int firstCardValue();
	Game * WhichGame();
	Lobby* WhichLobby();
	bool IsOut();
	void SetOut(bool);

};

