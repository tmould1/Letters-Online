#include "Lobby.h"



Lobby::Lobby()
{
	Game * tmpGamePtr = new Game("initGame", 3);
	tmpGamePtr->AcquireLobby(this);
	games.push_back(tmpGamePtr);
}


Lobby::~Lobby()
{
	for (gameIterator = games.begin(); gameIterator != games.end(); ) {
		delete *gameIterator;
	}
}
std::string Lobby::GetGameList() {
	std::string gameList;
	for (gameIterator = games.begin(); gameIterator != games.end(); gameIterator++) {
		gameList += (*gameIterator)->GetName();
		gameList += " ";
		gameList += (*gameIterator)->GetCurrentPlayerCount();
		gameList += " ";
		gameList += (*gameIterator)->GetMaxPlayerCount();
		gameList += " ";
	}
	return gameList;
}
std::string Lobby::GetNumGames() {
	std::string numString;
	numString = games.size();
	return numString;
}

std::string Lobby::GetPlayers() {
	std::string playerList;
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		playerList += (*playerIterator)->GetName();
	}
	return playerList;
}
std::string Lobby::GetNumPlayers() {
	std::string numString;
	numString = players.size();
	return numString;
}
void Lobby::MakeGame(std::string name, int maxPlayers){
	Game * tmpGamePtr = new Game(name, maxPlayers);
	tmpGamePtr->AcquireLobby(this);
	games.push_back(tmpGamePtr);
}

std::string Lobby::ReportState() {
	std::string outString;
	outString += GetNumGames();
	outString += GetGameList();
}
