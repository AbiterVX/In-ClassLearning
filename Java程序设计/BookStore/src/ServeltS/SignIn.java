package ServeltS;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Vector;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import Basics.Book;
import Basics.DataBase;
import Basics.User;

/**
 * Servlet implementation class SignIn
 */
@WebServlet("/SignIn")
public class SignIn extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public SignIn() {
        super();     
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{		
		HttpSession session=request.getSession();
		int mindex=(int)session.getAttribute("Mindex");
		mindex=1;
		session.setAttribute("Mindex", mindex);
		String id=request.getParameter("Id");
		String pw=request.getParameter("PassWord");
		DataBase db=new DataBase();
		User user=db.SignIn(id);
		db.close();
		RequestDispatcher rd;
		System.out.println(user.GetPassWord());
		if(user!=null && user.GetPassWord().equals(pw))
		{
			System.out.println("into suc");
			session.setAttribute("User", user);
			Cookie cookie_name=new Cookie("username",user.GetUserName());
			Cookie cookie_pd=new Cookie("password",user.GetPassWord());
		
			Cookie  cookie_id=new Cookie("id",user.GetId());
			
			response.addCookie(cookie_id);
			response.addCookie(cookie_pd);
			response.addCookie(cookie_name);
			//rd=getServletContext().getRequestDispatcher("/MainWindow.jsp");	
			response.sendRedirect("MainWindow.jsp");
		}
		else
		{
			//rd=getServletContext().getRequestDispatcher("/SignIn.jsp");	
			response.sendRedirect("SignIn.jsp");
		}
		/*
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}	
		*/	
		/*
		DataBase database=(DataBase)session.getAttribute("DataBase");						
		User user=database.SignIn(request.getParameter("Id"), request.getParameter("PassWord"));									
		/*------------------------------------*/
		/*
		RequestDispatcher rd;
		if(user!=null) {
			request.setAttribute("User", user);				
			rd=getServletContext().getRequestDispatcher("/MainWindow.jsp");		
		}
		else {	
			rd=getServletContext().getRequestDispatcher("/SignIn.jsp");	
		}
		
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}		
			*/					
	}
}







