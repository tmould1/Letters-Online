
#include "Command.h"
#include <iostream>

Command::Command()
{
	argList = new vector<std::string>();
	// Populate arglist from CmdList
}

Command::~Command() {
}

void Command::GetClient(Client * actor) {
	clientActor = actor;
}

// All Commands Should be Initialized before Executing.  Consider Initialization in Execute
void Command::Initialize(string inArgs) {
	cmdArgs = inArgs;
	splitArgs();
        sm = sm->get();
}

void Command::splitArgs() {
	stringstream ss(cmdArgs);
	string arg;
	char delimiter = ' ';

	while (getline(ss, arg, delimiter)) {
		argList->push_back(arg);
	}
}


// Command Execute Section
// Commands From Client

bool DisconnectCommand::Execute() {
	HaxorSocket * clientSock = &(clientActor->getSocket());
	sm->releaseClient(clientActor);
	return true;
}

bool NewAccountCommand::Execute() {
	Account * tempAccount;
	string name, pass, ip, email, admin;
	bool bAdmin = false;
	bool success = false;

        if ( argList->size() == 6 ) {
  	  name = argList->at(1);
	  pass = argList->at(2);
	  ip = argList->at(3);
	  email = argList->at(4);
          admin = argList->at(5);
	  if (admin == "true") {
		bAdmin = true;
	  }
          else {
     		bAdmin = false;
	  }
	  tempAccount = new Account(name, pass, ip, email, bAdmin);
	  if (sm->AddAccount(*tempAccount)) {
		  clientActor->setAccount(tempAccount);
		success = true;
		// Success
	  }
	  else {
		// Failure
	  }

	  delete tempAccount;
        }

	return success;
}

bool LoginCommand::Execute() {
	bool status = false;
	sm->checkAccount(argList->at(1), argList->at(2), argList->at(3));
        status = true;
        return status;
}

bool CreateGameCommand::Execute() {
	Player * pc = clientActor->GetPlayer();
	myLobby = pc->WhichLobby();
	myLobby->MakeGame(argList->at(1), stoi(argList->at(2)));
}

// Commands From Server

bool LoginCheckCommand::Execute() {
	bool status = false;
	if (cmdArgs.find("Login") != std::string::npos) {
		std::cout << "Sending Back Login Success Info" << endl;
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck Login " +argList->at(4));
	}
	else if (cmdArgs.find("NewAccount") != std::string::npos) {
		sm->SendMessageToSocket(clientActor->getSocket(), "LoginCheck NewAccount " + argList->at(6));
	}
	status = true;
	return status;
}

// PRECONDITIONS :
// Assume initialize is called,
// cmdArgs Populated
// We have received a client request to play a card, we assume it is legit.
// RESPONSE : 
// What Actions should the server take?  
//    Player must put card from hand into their discard pile

//****** begin switch
//    We must apply the effect of the card, (e.g. apply protection, make a guess, compare hands, target player discards hand, trade hands
//    This may result in someone being marked as "out" (isOut()) for the remainder of the round
//****** end switch/selection

//    AdvanceActivePlayer Handles the following
//    Player Signals Pass of Turn to Game Instance
//    Check for Winner
//    Deal Card
bool PlayCardCommand::Execute() {
	// Example Input Line that provokes PlayCard Cloning :
	//  "Play 4"
	//  "Play 1 Joe 3" - Play a Guess card on joe guessing that he holds a 3
	//  "Play 3 Joe" - Compare & kill lesser. == -> no effect
	//  "Play 7"
	Command* tempCmd;
	int card[8];
	int cardNum = stoi(argList->at(1));
	Player * instigator = clientActor->GetPlayer();
	Game * game = instigator->WhichGame();
	
	// Command::clientActor is set by Command::GetClient
	// Client includes getSocket() and GetPlayer() for access other info
	
	//Choose
	///discard the card as it is played
	  // Card 1 :
	//switch (*card) {
	switch (cardNum){
	case 1 : {
		Player * victim = game->GetPlayerByName(argList->at(2));
		Card * TargetCard = new Card(stoi(argList->at(1)));
		// Case 1 : Player chooses the correct card
		if (victim->HasCard(TargetCard)) {
			victim->DiscardCard(TargetCard);
			victim->SetOut(true);
		}
		// Case 2 : Player chooses the incorrect card
		else {
			
		}
		delete TargetCard;
	}break;
	case 2: {
		// View another player's card
		Player * victim = game->GetPlayerByName(argList->at(2));
		Card * ViewedCard = new Card(victim->firstCardValue());
		Command * tempCommand = sm->getCommandClone("ViewCard");
		tempCommand->GetClient(instigator->WhichClient());
		tempCommand->Initialize("ViewCard " + ViewedCard->GetID());
		sm->SendToOutBox(tempCommand);
		delete ViewedCard;
	}break;
	case 3: {
		Player * victim = game->GetPlayerByName(argList->at(2));
		// Case 1 : Player has a lower Card, they is out
		if (instigator->firstCardValue() < victim->firstCardValue()) {
			instigator->SetOut(true);
		}
		// Case 2 : Player wins, victim is out
		else if (instigator->firstCardValue() > victim->firstCardValue()) {
			victim->SetOut(true);
		}
		// Case 3 : Tie
		else {

		}
		// 
	}break;
	case 4: {
		// Immunity to all played effects
		instigator->SetImmune(true);
	}break;
	case 5: {
		// Case 1 : Player chooses another player
		Player * victim = game->GetPlayerByName(argList->at(2));
		Card * TargetCard = new Card(stoi(argList->at(1)));
		victim->DiscardCard(TargetCard);
		// Case 2 : Player chooses self
		instigator->DiscardCard(TargetCard);
		delete TargetCard;
	}break;
	case 6: {
		// Swap cards with a player
		Player * victim = game->GetPlayerByName(argList->at(2));
		Card * tempCard = new Card(instigator->getCard());
		instigator->ReceiveCard(victim->getCard());
		victim->ReceiveCard(tempCard);
		delete tempCard;
	}break;
	case 7: {
		// Conditional
	}break;


	}


	// Check for a Winner
	if (game->CheckForWinner()) {
		Player * winner = game->GetWinner();
		string cmdText = "GameWinner ";
		Command * winCommand = sm->getCommandClone("GameWinner");
		cmdText += winner->GetName();
		winCommand->GetClient(clientActor);
		winCommand->Initialize(cmdText);
		sm->SendToOutBox(winCommand);
	}
	else {
		// Let the Game Know that the Player has finished his turn.
		game->AdvanceActivePlayerMarker();
	}
}

bool GameWinnerCommand::Execute() {
	Game * thisGame = clientActor->GetPlayer()->WhichGame();
	thisGame->SendMessageToPlayers(cmdArgs);
}
bool ViewCardCommand::Execute() {
	sm->SendMessageToSocket(clientActor->getSocket(), cmdArgs);
}