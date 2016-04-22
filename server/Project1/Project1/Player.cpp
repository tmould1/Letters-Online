#include "Player.h"



Player::Player()
{
	myClient = NULL;

}

Player::Player(Client* instigator) {
	myClient = instigator;

}

Player::~Player()
{
}

Lobby * Player::WhichLobby() {
	return myLobby;
}

void Player::CreateGame(string name, int numPlayers) {

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


