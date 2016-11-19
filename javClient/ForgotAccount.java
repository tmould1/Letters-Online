
/************************************************/
/*
/* Filename: ForgotAccount.java
/*
/* Purpose: Allows the user to input an email and grab the corresponding account info.
/*
/* Author: Ryan Ngo
/*
/* Change Log:
/* {Date}: {Description}
/* 11/16/16: added basic email 
/*
/* 
/*
/*
/************************************************/

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.ResultSet;

/**
 * Servlet implementation class ForgotAccount
 */
public class ForgotAccount extends HttpServlet {
	private static final long serialVersionUID = 1L;

    // Supply your SMTP credentials below. Note that your SMTP credentials are different from your AWS credentials.
    static final String SMTP_USERNAME = "AKIAIAU6JTT3VPC56MYA";  // Replace with your SMTP username.
    static final String SMTP_PASSWORD = "AowbDa01DMOTBJ2Am09JrljHSMn7aP3pF1gImq9tzac7";  // Replace with your SMTP password.
       
 // Amazon SES SMTP host name. This example uses the US West (Oregon) region.
    static final String HOST = "email-smtp.us-west-2.amazonaws.com";    
    
    // The port you will connect to on the Amazon SES SMTP endpoint. We are choosing port 25 because we will use
    // STARTTLS to encrypt the connection.
    static final int PORT = 25;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ForgotAccount() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		final PrintWriter out = response.getWriter();
		Properties props = System.getProperties();
    	props.put("mail.transport.protocol", "smtps");
    	props.put("mail.smtp.port", PORT); 
    	
    	// Set properties indicating that we want to use STARTTLS to encrypt the connection.
    	// The SMTP session will begin on an unencrypted connection, and then the client
        // will issue a STARTTLS command to upgrade to an encrypted connection.
    	props.put("mail.smtp.auth", "true");
    	props.put("mail.smtp.starttls.enable", "true");
    	props.put("mail.smtp.starttls.required", "true");

        // Create a Session object to represent a mail session with the specified properties. 
    	Session session = Session.getDefaultInstance(props);

    	String FROM = "h4x0rz4330@gmail.com";
    	String TO = request.getParameter("email");
    	String SUBJECT = "Message from h4x0rz4330!";
    	String BODY = "";			
    	String DB_URL = "jdbc:mysql://localhost:3306/Careers2You";
    	
    	//User credentials
    	String username = "";
    	String password = "";
    	
		// Database credentials
		String USER = "worker";
		String PASS = "";
		Connection conn = null;

		//Register JDBC driver
		try {
			Class.forName("com.mysql.jdbc.Driver");
			//Open a connection
			conn = (Connection) DriverManager.getConnection(DB_URL,USER,PASS);
			//Execute a query
			String sql;
			sql = "Select * from user where email = ?";
			PreparedStatement psql = (PreparedStatement) conn.prepareStatement(sql);
			psql.setString(1, TO);
			System.out.println(psql);
			ResultSet rs = (ResultSet) psql.executeQuery();
			if (!rs.next()){
				rs.close();
				psql.close();
				conn.close();
				out.println("0");
				System.out.println("User doesn't exist");
			}else{
				username = rs.getString("username");
				password = rs.getString("password");
				password = Encryptor.decrypt(Encryptor.key, Encryptor.initVector, password);
			}
		}catch(ClassNotFoundException | SQLException e) {
		// TODO Auto-generated catch block
			out.println("0");
			e.printStackTrace();
		}
		//Sending Message
        // Create a message with the specified information.
		if (username.equals("") || password.equals("")){
			out.println("0");
		}else{
			SUBJECT = "H@X0RZ Username and Password Recovery.";
			BODY = "<div><p>Hi this is your username and password:</p></div>"+
					"<div><p>Username: "+username+"</p></div>"+
					"<div><p>Password: "+password+"</p></div>";
	        MimeMessage msg = new MimeMessage(session);
	        try {
				msg.setFrom(new InternetAddress(FROM));
		        msg.setRecipient(Message.RecipientType.TO, new InternetAddress(TO));
		        msg.setSubject(SUBJECT);
		        msg.setContent(BODY,"text/html");
		        
		        Transport transport = session.getTransport();
		        
		        try
		        {
		            System.out.println("Attempting to send an email through the Amazon SES SMTP interface...");
		            
		            // Connect to Amazon SES using the SMTP username and password you specified above.
		            transport.connect(HOST, SMTP_USERNAME, SMTP_PASSWORD);
		        	
		            // Send the email.
		            transport.sendMessage(msg, msg.getAllRecipients());
		            System.out.println("Email sent!");
		            out.println("1");
		        }
		        catch (Exception ex) {
		        	out.println("0");
		            System.out.println("The email was not sent.");
		            System.out.println("Error message: " + ex.getMessage());
		        }
		        finally
		        {
		            // Close and terminate the connection.
		            transport.close();        	
		        }
			} catch (AddressException e) {
				// TODO Auto-generated catch block
				out.println("0");
				e.printStackTrace();
			} catch (MessagingException e) {
				out.println("0");
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
}
