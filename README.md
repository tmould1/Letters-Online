# Letters-Online
Beginning


To start the gameServer:
./server/Project1/Project1/server &
Default port set to 9999

Current Build should be stable.
To compile: /server/Project1/Project1/
make clean
make
To ensure good build.

cClient Communication
-- cClient was only built for testing server functionality
   - Thus, it is only viable for sending New Connection Commands
   - i.e. - NewAccount or Login
   -  And receiving the result, no persistent connection functionality is implemented
To test this:
./cClient/src/echoClient toddmoulder.com "Login <UserName> <UserPass> <CurrentIP>" 9999
or
./cClient/src/echoClient toddmoulder.com "NewAccount <UserName> <UserPass> <CurrentIP> <emailaddress> <isAdmin?>" 9999

JavaClient Communcation
