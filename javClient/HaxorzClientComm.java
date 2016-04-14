//package haxorzclientcomm;
// @author Jonathan Nguyen

import java.net.*;
import java.io.*;

public class HaxorzClientComm {

    public static void main(String[] args) throws IOException { 
        Socket sock = null;
        PrintWriter out = null;
        BufferedReader read = null;
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String host = "Till and Wodd";
        try{
            sock = new Socket("toddmoulder.com",47888);
            out = new PrintWriter(sock.getOutputStream(), true);
            read = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        }
        catch (UnknownHostException e){
            System.err.printf("Don't know about host: %s", host);
            System.exit(1);
        }
        catch (IOException ioe){
            System.err.printf("Couldn't get I/O for connection to: %s", host);
            System.exit(1);
        }
        
        String serverMsg;
        String userMsg;
        while((serverMsg = read.readLine()) != null){
            System.out.printf("Server: %s", serverMsg);
            if(serverMsg.equals("DC"))
                break;
            if((userMsg = in.readLine()) != null){
                System.out.printf("Client: %s", userMsg);
                
            }
        }
        
        out.close();
        read.close();
        in.close();
        sock.close();
    }
        
}
