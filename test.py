import socket
import select

testSock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

def Connect( mySock ):
    mySock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
    mySock.connect( ('toddmoulder.com', 9999) )

def Disconnect( mySock ):
    mySock.send("Disconnect")

def Login(mySock):
    mySock.send("Login Todd");
    var = mySock.recv( 1024 )
    print var
    
def TestRun():
    global testSock
    testSock.connect( ('toddmoulder.com', 9999) )
    testSock.send("NewAccount ryno@onyr.com false")
    serverMsg = testSock.recv( 1024 )
    print serverMsg
    testSock.send("CreateGame TestGame 4 Todd")
    serverMsg = testSock.recv( 1024 )
    print serverMsg   

    

def Disconnect():
    global testSock
    testSock.send("Disconnect")

def CreateGame( name, maxPlayers, creatorName ) :
    testSock.send("CreateGame" + name + str(maxPlayers) + creatorName)

