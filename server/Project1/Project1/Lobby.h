#pragma once
#include <vector>
#include "Game.h"
#include "Player.h"

class Lobby
{
private:
	std::vector<Game *> games;
	std::vector<Game *>::iterator gameIterator;
	std::vector<Player *> players;
	std::vector<Player *>::iterator playerIterator;
	int maxGames;
	int maxPlayers;
public:
	Lobby();
	~Lobby();
	string GetGameList();
	string GetNumGames();
	string GetPlayers();
	string GetNumPlayers();
	void MakeGame(string name);

};

