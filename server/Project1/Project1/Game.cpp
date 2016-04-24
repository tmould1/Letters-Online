#include "Game.h"
#include <ctime>
#include <cstdlib>


Game::Game()
{
	name = "DefaultGame";
	maxPlayers = 4;
	srand(time(NULL));
	loadDeck();
	hasStarted = false;
	sm = sm->get();
}

Game::Game(string gameName, int max) {
	name = gameName;
	maxPlayers = max;
	srand(time(NULL));
	loadDeck();
	hasStarted = false;
	sm = sm->get();
}

void Game::AcquireLobby(Lobby * mine) {
	myLobby = mine;
}

void Game::loadDeck() {
	for (int i = 0; i < 5; i++) {
		actualCards[i] = new Card(1);
	}
	for (int j = 0; j < 2; j++) {
		actualCards[5 + j] = new Card(2);
	}
	for (int k = 0; k < 2; k++) {
		actualCards[7 + k] = new Card(3);
	}
	for (int l = 0; l < 2; l++) {
		actualCards[9 + l] = new Card(4);
	}
	for (int l = 0; l < 2; l++) {
		actualCards[11 + l] = new Card(5);
	}
	actualCards[13] = new Card(6);
	actualCards[14] = new Card(7);
	actualCards[15] = new Card(8);

}


Game::~Game()
{
	for (int i = 0; i < 15; i++) {
		delete actualCards[i];
	}
}

void Game::ClaimPlayer(Player * newPlayer) {
	players.push_back(newPlayer);
}

void Game::Shuffle() {
	// Random Number Fun
	int randPos;
	int deckCount = 16;
	std::vector<Card *> shuffleDeck;

	for (int i = 0; i < 16; i++) {
		shuffleDeck.push_back(actualCards[i]);
	}

	for (int i = 0; i < 16; i++) {
		randPos = rand() % deckCount;
		deck.push_back(shuffleDeck.at(randPos));
		shuffleDeck.erase(shuffleDeck.begin() + randPos);
		deckCount--;
	}
}

void Game::StartGame() {
	Shuffle();
	faceDownCard = drawCard();
	if (players.size() == 2) {
		BurnThreeCard();
	}
	ActivePlayerIterator = players.begin();
	DealCard();
	// Pass ball to Client  =?=  send "UpdateGameInfo" Command to all players?
}

void Game::DealCard() {
	(*ActivePlayerIterator)->ReceiveCard(drawCard());
}

void Game::GiveCard(Player * toPlayer) {
	toPlayer->ReceiveCard(drawCard());
}

// drawCard
// @return Card * to the recently removed deck Card
Card* Game::drawCard() {
	Card * tmpCardPtr;
	tmpCardPtr = deck.front();
	deck.erase(deck.begin());
	return tmpCardPtr;
}

void Game::AdvanceActivePlayerMarker() {
	// Advance The Active Player Marker
	std::advance(ActivePlayerIterator, 1);
	if (ActivePlayerIterator == players.end()) {
		ActivePlayerIterator = players.begin();
	}
	// Check Winner Status
	// I.E. If Deck.empty() is true, check player with highest card
	//  Else, DealCard to
	GiveCard((*ActivePlayerIterator));
	// Wait for PlayCard Command
}

void Game::BurnThreeCard() {
	for (int i = 0; i < 3; i++) {
		burnPile.push_back(drawCard());
	}
}

std::string Game::GetName() {
	return name;
}

int Game::GetCurrentPlayerCount() {
	return players.size();
}

int Game::GetMaxPlayerCount() {
	return maxPlayers;
}

bool Game::CheckForWinner() {
	int numIn = 0;
	bool status = false;
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		if (!(*playerIterator)->IsOut()) {
			numIn++;
		}
	}
	if (numIn == 1) {
		status = true;
	}
	return status;
}

Player * Game::GetWinner() {
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		if (!(*playerIterator)->IsOut()) {
			break;
		}
	}
	return (*playerIterator);
}

Player* Game::GetPlayerByName(std::string tName) {
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		if ((*playerIterator)->GetName() == tName) {
			break;
		}
	}
	return (*playerIterator);
}

void Game::SendMessageToPlayers(std::string message) {
	Client * tClient;
	for (playerIterator = players.begin(); playerIterator != players.end(); playerIterator++) {
		tClient =(*playerIterator)->WhichClient();
		sm->SendMessageToSocket(tClient->getSocket(), message);
	}
}

std::string Game::Report() {
	std::string output;
	output = GetName();
	output += " " + GetCurrentPlayerCount();
	output += " " + GetMaxPlayerCount();
	return output;
}