
/************************************************/
/*
/* Filename: Register.java
/*
/* Purpose: Allows the user to register. creates cookie on register.
/*
/* Author: Ryan Ngo
/*
/* Change Log:
/* {Date}: {Description}
/* 10/24/16: add register function
/* 10/30/16: edited output for application
/* 11/16/16: edited to include email in registration 
/* 			 and changed encryption algorithm using Encryptor class
/*
/*
/* 
/*
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

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.ResultSet;
import com.mysql.jdbc.Statement;

/**
 * Servlet implementation class Register
 */
public class Register extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Register() {
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

		String email = request.getParameter("email");
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		password = Encryptor.encrypt(Encryptor.key, Encryptor.initVector, password);
		
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
			String sql = "Select count(*) from user where email = ?";
			PreparedStatement psql = (PreparedStatement) conn.prepareStatement(sql);
			psql.setString(1, email);
			ResultSet rs = (ResultSet) psql.executeQuery();
			rs.next();
			int num = rs.getInt(1);
			if (num > 0 || email == "" || username == "" || password == ""){
				rs.close();
				System.out.println("User already exists");
				out.print("0");
				psql.close();
				stmt.close();
				conn.close();
			}else{
				rs.close();
				sql = "Insert into user (Email, Username, Password) VALUES (?,?,?)";
				psql = (PreparedStatement) conn.prepareStatement(sql);
				psql.setString(1, email);
				psql.setString(2, username);
				psql.setString(3, password);
				psql.executeUpdate();
				System.out.println("User: "+username+" has been inserted");
				Cookie emailCookie = new Cookie("Email", email);
				Cookie userCookie = new Cookie("Username", username);
				Cookie passCookie = new Cookie("Password", password);
				response.addCookie(emailCookie);
				response.addCookie(userCookie);
				response.addCookie(passCookie);
				rs.close();
				psql.close();
				stmt.close();
				conn.close();
				out.println("1");
			}
		}catch (ClassNotFoundException | SQLException e){
			e.printStackTrace();
		}
		
	}

}
