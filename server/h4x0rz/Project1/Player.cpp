#include "Player.h"



Player::Player()
{
	myClient = NULL;
	isOut = false;
}

Player::Player(Client* instigator) {
	myClient = instigator;
	isOut = false;
	myClient->acquirePlayer(this);
}

Player::~Player()
{
	//Delete any new memory allocated specifically for Player
}

std::string Player::GetName(){
	myClient->GetName();
}

Lobby * Player::WhichLobby() {
	return myLobby;
}
Game* Player::WhichGame() {
	return myGame;
}
Client* Player::WhichClient() {
	return myClient;
}

void Player::ReceiveCard(Card* tCard){
	inHand.push_back(tCard);
}

void Player::CreateGame(std::string name, int numPlayers) {
	myGame = myLobby->MakeGame(name, numPlayers);
}

int Player::firstCardValue() {
	return inHand.at(0)->GetID();
}

bool Player::IsOut() {
	return isOut;
}
void Player::SetOut(bool status) {
	isOut = status;
}

// Play Card Command <-> Player Interaction
// PRECONDITION :
//  Command has been received from Client by Server,
//   We are in the middle of updating the game
//   
void Player::PlayCard(int cardID) {
	std::vector<Card *>::iterator it;
	for (it = inHand.begin(); it != inHand.end(); it++) {
		if ((*it)->GetID() == cardID) {
			discardPile.push_back(*it);
			inHand.erase(it);
		}
	}
}
bool Player::isTurn() {
	return myTurn;
}

void Player::SetTurn(bool status) {
	myTurn = status;
}

void Player::DiscardCard(Card * tCard) {
	for (cardIt = inHand.begin(); cardIt != inHand.end(); cardIt++) {
		if ((*cardIt)->GetID() == tCard->GetID()) {
			discardPile.push_back(*cardIt);
			inHand.erase(cardIt);
			break;
		}
	}
}

bool Player::HasCard(Card * inCard) {
	bool status = false;
	for (cardIt = inHand.begin(); cardIt != inHand.end(); cardIt++) {
		if ((*cardIt)->GetID() == inCard->GetID()) {
			status = true;
		}
	}
	return status;
}


// Guaranteed only one card in hand
Card* Player::GetCard() {
	Card * tmpCard = inHand.at(0);
	inHand.erase( inHand.begin() );
	return tmpCard;
}

bool Player::IsImmune() {
	return immune;
}

void Player::SetImmune(bool status) {
	immune = status;
}