import java.io.*;
import java.net.*;

public class ClientSocket {
	public static void main(String[] args) {
		String host = "<changeThis>";         //set to host IP
		try{
			Socket socket = new Socket(host, 9999);
			BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter output = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
		//output to server
			String out = null;
			while ((out = output.newLine()) != null) {      //needs revision
				out.println(out);
				out.flush();
			}
		//take input from the server
			String in = null;
			while ((in = input.readLine()) != null) {
				System.out.println(in);             //alter this to send string to another object
			}			
		//close the filestreams/socket	
			output.close();
			input.close();
			socket.close();			
		} catch (Exception error) {
			error.printStackTrace();
		}
	}
}
