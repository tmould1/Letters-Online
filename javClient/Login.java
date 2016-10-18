

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
			String id = Integer.toString(rs.getInt("ID"));
			String name = rs.getString("Username");
			String userPass = rs.getString("Password");
			if (name!=null){
				rs.close();
				if (pE.checkPassword(password, userPass)){
					Cookie u = new Cookie("UID", id);
					Cookie p = new Cookie("Password", userPass);
					u.setMaxAge(1800);
					p.setMaxAge(1800);
					response.addCookie(u);
					response.addCookie(p);
					out.print("login success");
				}else{
					out.print("login failed");
					System.out.println("login failed. password incorrect.");
				}
				stmt.close();
				conn.close();
			}else{
				rs.close();
				out.print("false, 404");
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
