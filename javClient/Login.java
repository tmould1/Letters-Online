
/************************************************/
/*
/* Filename: Client.js
/*
/* Purpose: Allows the user to login. Creates cookies on login
/*
/* Author: Ryan Ngo
/*
/* Change Log:
/* {Date}: {Description}
/* 10/24/16: add login function
/*
/************************************************/

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.jasypt.util.password.BasicPasswordEncryptor;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.ResultSet;
import com.mysql.jdbc.Statement;

/**
 * Servlet implementation class Register
 */
public class Login extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Login() {
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
		// TODO Auto-generated method stub
		final PrintWriter out = response.getWriter();
		
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		BasicPasswordEncryptor pE = new BasicPasswordEncryptor();
		
		String JDBC = "com.mysql.jdbc.Driver";
		String DBURL = "jdbc:mysql://localhost:3306/h4x0rz";
		
		String user = "h4x0rz";
		String pass = "Howuknowdis?";
		
		Connection conn = null;
		Statement stmt = null;
		
		try{
			Class.forName(JDBC);
			System.out.println("Connecting to db...");
			conn = (Connection) DriverManager.getConnection(DBURL, user,pass);
			System.out.println("Creating Statement...");
			stmt = (Statement) conn.createStatement();
			String sql = "Select * from user where Username = \'"+username+"\'";
			ResultSet rs = (ResultSet) stmt.executeQuery(sql);
			rs.next();
			String name = rs.getString("Username");
			String userPass = rs.getString("Password");
			if (name!=null){
				rs.close();
				if (pE.checkPassword(password, userPass)){
					Cookie userCookie = new Cookie("Username", name);
					Cookie passCookie = new Cookie("Password", userPass);
					userCookie.setMaxAge(1800);
					passCookie.setMaxAge(1800);
					response.addCookie(userCookie);
					response.addCookie(passCookie);
					out.print("true");
				}else{
					out.print("false");
					System.out.println("login failed. password incorrect.");
				}
				stmt.close();
				conn.close();
			}else{
				rs.close();
				out.print("false 404");
				System.out.println("login failed. user doesn't exist.");
				rs.close();
				stmt.close();
				conn.close();
			}
		}catch (ClassNotFoundException | SQLException e){
			e.printStackTrace();
		}
		
	}

}
