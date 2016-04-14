
   //  Loot Letter Threading Test

   #include <iostream>
   #include <thread>
   #include <vector>
   #include <cstdlib>
   #include <ctime>

   using namespace std;

   void clientLoop(  int id );
   void showCard(  int i );
   void buildDeck();

   const int maxClients = 16;

   vector< int> setDeck;
   int deckCount = 16;


   int main( int argc, char * argV[]) {
     thread  testThread;
     vector<thread> tVect ( maxClients );
     int i = 0;
      int randPos;
      int randCard;

     srand( time(NULL) );
     buildDeck();

     cout << "Max :" << maxClients << endl;

       for ( i = 0; i < maxClients; i++ ) {
         randPos  = rand() % deckCount;
         randCard = setDeck.at( randPos );
         tVect[i] = thread( clientLoop, randCard );
         tVect[i].join();
         setDeck.erase( setDeck.begin()+randPos );
         deckCount--;
     }

     cout << "Threads joined!" << endl;

     return 0;
   }

   void buildDeck() {
     for( int i = 0; i < 5; i++ ){
       setDeck.push_back(1);
     }
     for( int i = 0; i < 2; i++){
       setDeck.push_back(2);
       setDeck.push_back(3);
       setDeck.push_back(4);
       setDeck.push_back(5);
     }
     setDeck.push_back(6);
     setDeck.push_back(7);
     setDeck.push_back(8);
   }


   void clientLoop(  int id ) {

     showCard( id );

   }

   void showCard(  int i ) {

     switch (i) {
       case 1 :
	cout << "Found a Potted Plant\n\r"; break;
       case 2 :
        cout << "Found a Maul Rat\n\r"; break;
       case 3 :
        cout << "Found a Duck of Doom\n\r"; break;
       case 4 :
        cout << "Found a Wishing Ring\n\r"; break;
       case 5 :
        cout << "Found a Net Troll\n\r"; break;
       case 6 :
        cout << "Found a Dread Gazeebo\n\r"; break;
       case 7 :
        cout << "Found a Turbonium Dragon\n\r"; break;
       case 8 :
        cout << "Found a Loot\n\r"; break;
       default :
        cout << "Found a " << i << endl; break;
     }

   }
