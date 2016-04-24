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

void Player::ReceiveCard(Card*){
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


