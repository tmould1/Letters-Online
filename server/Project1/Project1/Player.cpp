#include "Player.h"



Player::Player()
{
	myClient = NULL;
	acquireServerManager();
}

Player::Player(Client* instigator) {
	myClient = instigator;
	acquireServerManager();
}

Player::~Player()
{
}

void Player::acquireServerManager() {
	sm = sm->get();
}

void Player::PlayCard(Card * toPlay) {
	Command * playCommand = sm->getCommandClone("PlayCard");
	switch (toPlay->GetID()) {
	case 1: {

		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	case 4: {
		break;
	}
	case 5: {
		break;
	}
	case 6: {
		break;
	}
	case 7: {
		break;
	}
	case 8: {
		break;
	}
	default: {
		break;
	}
	}
}
