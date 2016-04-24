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
	std::string tmpStr;
	for (gameIterator = games.begin(); gameIterator != games.end(); gameIterator++) {
		gameList += (*gameIterator)->GetName();
		gameList += " ";
		tmpStr = (*gameIterator)->GetCurrentPlayerCount();
		gameList += tmpStr;
		gameList += " ";
		tmpStr = (*gameIterator)->GetMaxPlayerCount();
		gameList += tmpStr;
		gameList += " ";
	}
	return gameList;
}
std::string Lobby::GetNumGames() {
	std::string numString;
	if (games.size() <= 0) {
		numString = "0";
	}
	else {
		numString = games.size();
	}
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
	if (players.size() <= 0) {
		numString = "0";
	}
	else {
		numString = players.size();
	}
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
	return outString;
}
