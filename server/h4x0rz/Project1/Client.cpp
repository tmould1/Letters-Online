#include "Client.h"

ClientManager* ClientManager::_instance = NULL;

Player* Client::GetPlayer() {
	return player;
}

void Client::makePlayer(Player * target) {
	player = target;
}

void Client::destroyPlayer() {
	delete player;
}
std::string Client::GetName(){
	account->getEmail();
}

bool Client::assignSocket(TCPServerSocket * server) {
	bool status = false;
	mySock->Initialize(server->accept());
	if (mySock->IsSet()) {
		status = true;
	}
	return status;
}

Client Client::operator=(const Client obj) {
	mySock = obj.mySock;
	return *this;
}

int Client::getSocketID() {
        int result = -1;
	if ( mySock != NULL && mySock->IsSet() ) {
	  result = mySock->GetID();
        }
	return result;
}

HaxorSocket& Client::getSocket() {
	return *mySock;
}

Client::Client(){
	mySock = new SocketAdapter();
	makePlayer(new Player());
}
Client::~Client() {
	delete mySock;
	destroyPlayer();
	delete account;
}

void Client::putMsg(vector<string> & msgVector, string msg) {
	// Mutex Lock
	msgVector.push_back(msg);
	// Mutex Unlock
}

string Client::getMsg( vector<string> & msgVector) {
	// Mutex Lock
	string temp = msgVector.front();
	msgVector.erase(msgVector.begin());
	//Mutex Unlock
	return temp;
}

void Client::recMsg(vector<string> & msgBuffer) {
	sm = sm->get();
	putMsg(msgBuffer, sm->GetMsgFromSocket(*mySock));
}

Account& Client::getAccount() {
	return *account;
}

void Client::setAccount(Account* inAcct) {
	account = inAcct;
}



// Client Manager Section BEGIN

ClientManager* ClientManager::get() {
	if ( _instance == NULL ) {
		_instance = new ClientManager();
	}
	return _instance;
}

bool ClientManager::findClient(Client & tClient) {
	bool status = false;
	vector<Client*>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ( (*iClient)->getSocketID() == tClient.getSocketID() ) {
			it = iClient;
			status = true;
			break;
		}
	}
	return status;
}

Client* ClientManager::findClientByID(int tID) {
	vector<Client*>::iterator iClient;
	for (iClient = clientVec.begin(); iClient != clientVec.end(); iClient++) {
		if ((*iClient)->getSocketID() == tID) {
			it = iClient;
			break;
		}
	}
	return (*it);
}

ClientManager::ClientManager() {
    Client * firstClient = new Client();
	it = clientVec.begin();
	it = clientVec.insert(it, firstClient);
}

void ClientManager::Initialize(){
	sm = ServerManager::get();
}



ClientManager::~ClientManager() {
	// Loop through clientVector and free memory
	delete _instance;
}

bool ClientManager::addClient(Client * inClient) {
	// Should need some checking to see if Client is already in the list
	// If they are, we could be dealing with a reconnect
	//  Or inappropriate access of a client Account

	// Player starts with a pointer to its client
	Player * tmpPlayerPtr = new Player(inClient);
	
	// And now client has a pointer to its player
	inClient->makePlayer(tmpPlayerPtr);

	// Add to list of clients to keep track of.
	it = clientVec.insert(it, inClient);
	return true;
}


bool ClientManager::removeClient(Client & outClient) {
	bool status = false;
	// Add Mutex, Semaphore, or Monitor
	// Critical Section BEGIN
	// Clean up and Remove the Client
	if (findClient(outClient)) {
		// Clean up the player; we are about to delete client
		outClient.destroyPlayer();
		// Close out the socket
		outClient.getSocket().Close();
		// "it" iterator is the thread-safe needy thing
		clientVec.erase(it);
		status = true;
	}
	// Critical Section END
	return status;
}

Client& ClientManager::getClient(string name) {
	return *(new Client());
}

void ClientManager::populateFDSets() {
	for (it = clientVec.begin(); it != clientVec.end(); it++) {
		sm->setDescriptor(&(*it)->getSocket());
	}

}

void ClientManager::handleExceptions() {
	for (it = clientVec.begin(); it != clientVec.end(); it++) {
		sm->HandleExceptionSockets(&(*it)->getSocket());
		// Save Client
		// Safely Remove Client
		removeClient(**it);
	}
}

void ClientManager::getInputFromClients() {
	for (it = clientVec.begin(); it != clientVec.end(); it++) {
		sm->checkInSet(&(*it)->getSocket());
	}
}
