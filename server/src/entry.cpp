   // Server Entry Point
   // LSU Letter
   // CSC3380 Class Project
   // Authors:  Hardika Patel
   //           Jonathan Nguyen
   //           Todd Moulder
   //           William Raziano

   //  Below contains licensing info for "PracticalSockets"
/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

   #include <iostream>
//   #include <socket>
   #include <thread>            // For cout, cerr
   #include <vector>
   #include "PracticalSocket.h" // For Socket, ServerSocket, and SocketException
   #include <cstdlib>           // For atoi()
   #include <pthread.h>         // For POSIX Threads

   using namespace std;

   const char * cardLocationStr = "../txt/cards.data";

   const int RCVBUFSIZE = 32;                // Restricting receiving to 32 bytes

   void HandleTCPClient( TCPSocket *sock );   // TCP client handling fxn
   void *ThreadMain( void *arg );             // Main program of thread

   bool startServer( int port );
   bool serverLoop();
   void shutDownServer();

   int main( int argc, char * argv[] ){
     bool serverStatus = false;

     if ( argc != 2 ) {
       cerr << "Usage: " << argv[0] << " <Server Port> " << endl;
       exit(1);
     }

     unsigned short serverPort = atoi( argv[1] );   // First arg, local port

     try {
       TCPServerSocket serverSock(serverPort);      // Socket descriptor for server

       for ( ; ; ) {
         //Create sep mem for client arg
         TCPSocket *clientSock = serverSock.accept();

         // Client Thread
         pthread_t threadId;
         if (pthread_create( &threadId, NULL, ThreadMain, (void *)clientSock) != 0){
           cerr << "Unable to create thread" << endl;
           exit(1);
         }
       }//End For
     } catch(SocketException &e){
       cerr << e.what() << endl;
       exit(1);
     }
     // Never reached

     return 0;
   }

   // TCP client handling function
   void HandleTCPClient(TCPSocket *sock) {
     cout << "Handling client ";
     try {
       cout << sock->getForeignAddress() << ":";
     } catch(SocketException &e){
       cerr << "Unable to get foreign address" << endl;
     }
     try {
       cout << sock->getForeignPort();
     } catch(SocketException &e) {
       cerr << "Unable to get foreign port" << endl;
     }
     cout << " with thread " << pthread_self() << endl;

     // SEnd recvd strign and receive again until end of transmission
     char echoBuff[RCVBUFSIZE];
     int recvMsgSize;
     while ((recvMsgSize = sock->recv(echoBuff, RCVBUFSIZE)) > 0){ // Zero is end of transmission
       // Echo msg to client
       sock->send(echoBuff, recvMsgSize);
     }
     // Destructor closes Socket
   }

   void *ThreadMain(void *clientSock) {
     // Guarantess that thread resources are deallocated upon return
     pthread_detach(pthread_self());

     // Extract socket file descriptor from argument
     HandleTCPClient((TCPSocket*) clientSock);

     delete (TCPSocket *) clientSock;
     return NULL;
   }
   bool startServer( int port ){
   	bool success = false;
   	// Load Cards
   	// Start Lobby
   	// Start Game0
   	// set up listen(), maybe? listen may have to be in threadpool
     return success;
   }
   bool serverLoop(){
     bool serverState = true;
     // Check for new connections
     //  Add new thread for each
     // Update State of each client, game and lobby
     // check for funny things,
     return serverState;
   }
   void shutDownServer(){
     // Clean up threads
     // Clean up Memory
     // Clean up Sockets
     // Log shutdown conditions "../log/TIMEDATESTAMP.log"
   }
