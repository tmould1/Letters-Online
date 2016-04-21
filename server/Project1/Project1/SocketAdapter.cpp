#include "SocketAdapter.h"



SocketAdapter::SocketAdapter()
{
	set = false;
	msgLength = 1025;
}


SocketAdapter::~SocketAdapter()
{
}

bool SocketAdapter::IsSet() {
	return set;
}

void SocketAdapter::Initialize(TCPSocket* tcpSockPtr) {
	adaptee = tcpSockPtr;
	set = true;
}

void SocketAdapter::Send(std::string msg)
{
        msg += "\n";
        if(  IsSet() ) {
		adaptee->send((void *)msg.c_str(), msg.length()+1);
        }
}


std::string SocketAdapter::Receive()
{
	string message;
	char* cmessage = new char[msgLength];
	adaptee->recv((void*)cmessage, msgLength);
	message = cmessage;
	return message;
}


void SocketAdapter::Socket()
{
	socketID = adaptee->getSockDesc();
}

void SocketAdapter::Close() {
	delete adaptee;
}