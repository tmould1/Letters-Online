package haxorzclientcomm;
// @author Jonathan Nguyen

import java.net.*;
import java.io.*;
import java.util.Scanner;
//import java.util.concurrent.

public class HaxorzClientComm {

    public static void main(String[] args) throws IOException { 
        
        // Get login input from user
        // See UI code to merge
        
        Scanner userIn = new Scanner(System.in); 
        boolean newAcct = true;                // Placeholder, replace with UI
        String username = userIn.next();       // ^
        String password = userIn.next();       // ^
        String ip = InetAddress.getLocalHost().getHostAddress();
        String email = null;
        
        //For New Account case, display additional box
        if(newAcct = true){
            //Place UI input for newAcct here
        }
        
        //Be sure to check for empty fields above.

        // Create clientside socket
        Socket sock = null;
        PrintWriter output = null;
        try{
            sock = new Socket("toddmoulder.com", 9999);    //47888
            output = new PrintWriter(new OutputStreamWriter(sock.getOutputStream()));
        }
        // Error catch incase of wrong host
        catch (UnknownHostException e){
            System.err.println("Don't know about host: Haxorz");
            System.exit(1);
        }
        catch (IOException ioe){
            System.err.println("Couldn't get I/O for connection to: Haxorz");
            System.exit(1);
        }
        
        //Test sample of user input, remove later
        
        
        // Send login info
        if (newAcct = true){
            boolean isAdmin = false;
            output.write("Login" + username + " " + password + " " + ip + " " + email + " " + "false");
            output.flush();
        }
        else{
            output.write("Login " + username + " " + password + " " + ip);
            output.flush();
        }
        
        //Test
        
        String servMsg = null;
        //Test with new writer
        System.out.println("Hi");
        
        /*
        while (servMsg == null){
            long start = System.currentTimeMillis();
            int wait = 200;
            while (System.currentTimeMillis() - start < wait){
                servMsg = output.toString();//sock.getInputStream().toString();
            }
        }*/
        servMsg = output.toString();
        String[] update = servMsg.split(" ");
        System.out.println(update[0]);
        
        
        // Set up communications.
        // Msgs are for holding strings after receiving or before sending.
        // servIn is potentially not needed
        String userMsg;
        String winner = null;
        //Scanner servIn = new Scanner(sock.getInputStream());
        
        //Load Lobby for the first time
        output.write("RefreshLobby");
        output.flush();
        servMsg = sock.getInputStream().toString();
        update = servMsg.split(" ");
        
        //n -> number of games
        Game[] gameList = new Game[50];
        int listCount = 0;
        
        for (int n = 2; n < 2 + (Integer.parseInt(update[0]) * 3); n++){
            Game newGame = new Game(update[n], Integer.parseInt(update[n+1]), Integer.parseInt(update[n+2]));
            gameList[listCount] = newGame;
            listCount++;
            n += 2;
        }
        //Put code to display lobby, based on gameList, an arrray of games
        
        //Disable refresh button for 20 seconds. Display text.
        //if (refreshButton pressed), call refreshTimer thread to run
        //(new.HaxorzClientComm()).start();
        
        // Client loop
        while(true){        //While app is open
            //Get server input
            long start = System.currentTimeMillis();
            int wait = 200;
            while (System.currentTimeMillis() - start < wait){
                servMsg = sock.getInputStream().toString();
            }
            
            //Send RefreshLobby every 60sec on which end?
            
            // Apply update if any
            update = servMsg.split(" ");
            
            if (update[0].equals("UpdateLobby")){
                int numGames = Integer.parseInt(update[1]);
                for (int i = 0; i < numGames; i++){
                    //Create Game object? or just display on UI?
                    listCount = 0;
        
                    for (int n = 2; n < 2 + (Integer.parseInt(update[0]) * 3); n++){
                        Game newGame = new Game(update[n], Integer.parseInt(update[n+1]), Integer.parseInt(update[n+2]));
                        gameList[listCount] = newGame;
                        listCount++;
                        n += 2;
                    }
                }
                
            }
            
            //Search for game in gameList, update only non-final variable
            if(update[0].equals("UpdateGame")){
                for (int i = 0; i<50; i++){
                    if (gameList[i].getName().equals(update[1])){
                        gameList[i].setCurrent(Integer.parseInt(update[2]));
                        break;
                    }
                }
            }
            
            //Get user input
            //if refresh button pressed
                //be sure to check for full game using vars
            
            
            //Nested game loop
            //if ()       //If making game
            if (true){  //if a game is selected
                //Display game screen
                
                //Keep checking until game is full.
                start = System.currentTimeMillis();
                while (System.currentTimeMillis() - start < wait){
                    servMsg = sock.getInputStream().toString();
                    update = servMsg.split(" ");
                    int i = 0;
                    if (update[0].equals("UpdateGame")){
                        for (i = 0; i<50; i++){
                            if (gameList[i].getName().equals(update[1])){
                                gameList[i].setCurrent(Integer.parseInt(update[2]));
                                break;
                            }
                        }
                        gameList[i].setCurrent(Integer.parseInt(update[2]));
                    }
                    if (gameList[i].getCurrent() == gameList[i].getMax()){
                        break;
                    }
                }
                //CurrentPlayers now equals MaxPlayers. Initialize Game.
                
                        
                //Game loop
                Game newGame = new Game();
                while(winner == null){
                    start = System.currentTimeMillis();
                    while (System.currentTimeMillis() - start < wait){
                        servMsg = sock.getInputStream().toString();
                    }
                    
                    //Create game
                        newGame.setName(update[1]);
                        newGame.setCurrent(Integer.parseInt(update[2]));
                        newGame.setMax(Integer.parseInt(update[3]));
                    
                }
                // Display winner
                winner = newGame.getWinner();
            }
            
            //Create Game object, call method using update as arg
        
        
        // Merge with UI
        
        
        // Close out things
        //output.write("Disconnect");
        output.flush();
        output.close();
        //servIn.close();
        userIn.close();
        sock.close();
        }
    }
}

//Lobby class?

class Card{
    private int value;
    
    public Card(int val){
        value = val;
        //Associate image
    }
    
    public int getVal(){
        return value;
    }
}

class Player{
    private String username;
    private int isOut = 0;      //0 if still in round. 1 if out of round.
    private int isTurn = 0;
    
    public Player(){
        
    }
    
    //Play Card command
    public String play1(Player target, int guess){
        String ret = "Play 1 " + target + " " + guess;
        return ret;
    }
    
    public String play2(Player target){
        String ret = "Play 2 " + target;
        return ret;
    }
    
    public String play3(Player target){
        String ret = "Play 3 " + target;
        return ret;
    }
    public String play4(Player self){
        String ret = "Play 4 " + self;
        return ret;
    }
    public String play5(Player target){
        String ret = "Play 5 " + target;
        return ret;
    }
    public String play6(Player target){
        String ret = "Play 6" + target;
        return ret;
    }
    public String play7(){
        String ret = "Play 7";
        return ret;
    }
    public String play8(){
        String ret = "Play 8";
        return ret;
    }
    
    public void setTurn(int set){
        isTurn = set;
    }
    
    public void setOut(int set){
        isOut = set;
    }
}

class Game{
    private int currPlayers;
    private int maxPlayers;
    private int winCond;
    private String gameName;
    private String winPlay;

    public Game(){
        winPlay = "n/a";
    }
    
    public Game(String name, int cPlay, int mPlay){
        currPlayers = cPlay;
        maxPlayers = mPlay;
        gameName = name;
    }
    
    //For receiving
    public void cmdLine (String[] cmd){
        //LoginCheck command
            if (cmd[0].equals("LoginCheck")){
                if (cmd[1].equals("Login")){
                    if (cmd[2].equals("1")){
                        //Load lobby
                    }
                    else{
                        //Return incorrect login
                    }
                }
                else if (cmd[1].equals("NewAccount")){
                    if (cmd[2].equals("1")){
                        //Create account
                        //Load lobby
                    }
                    else{
                        //Return invalid accoung creation
                    }
                }
            }
            
            //UpdateGame command
            else if (cmd[0].equals("UpdateGame")){
                String gameName = cmd[1];
                int currPlayers = Integer.parseInt(cmd[2]);
                int maxPlayers = Integer.parseInt(cmd[3]);
                winPlay = cmd[4];
                
                //Move to create game, this is for update only
                //Game newGame = new Game(currPlayers, maxPlayers, gameName){
                    
            }
                // Merge with UI to Display gameName, currPlayers, and maxPlayers
                
            else if (cmd[0].equals("UpdateLobby")){
                
            }
        }
            //UpdatePlayer command
            

    public String getName(){
        return gameName;
    }
    
    public void setName(String s){
        gameName = s;
    }
    
    public int getCurrent(){
        return currPlayers;
    }
    
    public void setCurrent(int i){
        currPlayers = i;
    }
    
    public int getMax(){
        return maxPlayers;
    }
    
    public void setMax(int i){
        maxPlayers = i;
    }
    
    public int getWinCond(){
        return winCond;
    }
    
    public void setWinCond(int i){
        winCond = i;
    }
    
    public String getWinner(){
        return winPlay;
    }
}