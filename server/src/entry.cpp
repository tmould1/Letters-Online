   // Server Entry Point
   // LSU Letter
   // CSC3380 Class Project
   // Authors:  Hardika Patel
   //           Jonathan Nguyen
   //           Todd Moulder
   //           William Raziano

   #include <iostream>
//   #include <socket>
   #include <thread>
   #include <vector>

   using namespace std;

   const char * cardLocationStr = "../txt/cards.data";

   bool startServer( int port );
   bool serverLoop();
   void shutDownServer();

   int main( int argc, char * argv[] ){
     bool serverStatus = false;

     // In future, listenPort = toInt(argv[1 or 2])
     //  startup will happen as ./server 9999
     int listenPort = 9999;
     // Server Initialization
        serverStatus = startServer( listenPort );
   	 // Server Main Loop
        while ( serverStatus ){
          serverStatus = serverLoop();
        }
   	 // Server ShutDown
   	return 0;
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
