package ServeltS;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import Basics.DataBase;
import Basics.User;

/**
 * Servlet implementation class Register
 */

@WebServlet("/Register")
public class Register extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public Register() {
        super();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{
	    String name=request.getParameter("Name");
	    String pd=request.getParameter("PassWord");
	    String type=request.getParameter("type");
	    User user=new User("-1",name,pd,Integer.valueOf(type),1000);
		DataBase db=new DataBase();
		user=db.Register(user);
		db.close();
		HttpSession session=request.getSession();
		if(user!=null && !user.GetId().equals("-1"))
		{
			session.setAttribute("User", user);
			Cookie cookie_name=new Cookie("username",user.GetUserName());
			Cookie cookie_pd=new Cookie("password",user.GetPassWord());
		
			Cookie  cookie_id=new Cookie("id",user.GetId());
			
			response.addCookie(cookie_id);
			response.addCookie(cookie_pd);
			response.addCookie(cookie_name);
			
			response.sendRedirect("RegisterResult.jsp");
		}
		else
		{
			response.sendRedirect("Register.html");
		}
		/*
		RequestDispatcher rd=getServletContext().getRequestDispatcher("/RegisterResult.jsp");			
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}	
			*/												
	}

}




