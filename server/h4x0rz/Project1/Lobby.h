#pragma once
#include <vector>
#include <string>
#include "Game.h"
#include "Player.h"

class Game;
class Player;

class Lobby
{
private:
	std::vector<Game *> games;
	std::vector<Game *>::iterator gameIterator;
	std::vector<Player *> players;
	std::vector<Player *>::iterator playerIterator;
	int maxGames;
	int maxPlayers;
	ServerManager * sm;
public:
	Lobby();
	~Lobby();
	void Initialize();
	void acquirePlayer(Player *);
	void releasePlayer(Player *);
	std::string GetGameList();
	std::string GetNumGames();
	std::string GetPlayers();
	std::string GetNumPlayers();
	Game * MakeGame(std::string name, int maxPlayers);
	void SendMessageToPlayers(std::string message);
	std::string ReportState();

};

