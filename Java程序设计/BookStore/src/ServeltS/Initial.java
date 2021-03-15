package ServeltS;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Vector;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;



import Basics.Book;
import Basics.DataBase;
import Basics.User;

/**
 * Servlet implementation class Initial
 */

public class Initial extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public Initial() {
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
		Cookie[]cookies=request.getCookies();
		DataBase db=new DataBase();
		if(cookies!=null)
		{
			for(int i=0;i<cookies.length;i++)
			{
				if(cookies[i].getName().equals("id"))
				{
					User user=db.SignIn(cookies[i].getValue());
					session.setAttribute("User", user);
				}
			}
		}
		boolean firstremove=true;
		session.setAttribute("firstremove", firstremove);
		Vector<Book>ans=(Vector<Book>)session.getAttribute("Result");
		//ans=db.search_top();
		Integer mindex=(Integer)session.getAttribute("Mindex");
		if(mindex==null)
		{
			mindex=1;
		}
		ans=db.nextPage(mindex, 6);

		if(ans==null || ans.size()==0)
		{
			mindex--;
		}
		else
		{
			session.setAttribute("Result", ans);			
		}
		session.setAttribute("Mindex", mindex);
        db.close();
	}
}








