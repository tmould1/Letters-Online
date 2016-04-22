#include "Lobby.h"



Lobby::Lobby()
{
	games.push_back(new Game());
}


Lobby::~Lobby()
{
	for (gameIterator = games.begin(); gameIterator != games.end(); ) {
		delete *gameIterator;
	}
}
string Lobby::GetGameList() {
	string gameList;
	for (gameIterator = games.begin(); gameIterator != games.end(); gameIterator++) {
		gameList += (*gameIterator)->GetName();
		gameList += " ";
	}
	return gameList;
}
string Lobby::GetNumGames() {
	string numString;
	numString = games.size();
	return numString;
}

string Lobby::GetPlayers() {
	string playerList;
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		playerList += (*playerIterator)->GetName();
	}
}
string Lobby::GetNumPlayers() {
	string numString;
	numString = players.size();
	return numString;
}
