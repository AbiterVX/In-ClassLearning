package ServeltS;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import Basics.DataBase;
import Basics.User;

/**
 * Servlet implementation class BuyBook
 */
@WebServlet("/BuyBook")
public class BuyBook extends HttpServlet {
	private static final long serialVersionUID = 1L;       
    public BuyBook() {
        super();        
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{						
		String Remain=request.getParameter("remain");
		HttpSession session=request.getSession();
		User user=(User)session.getAttribute("User");
		String bookid=request.getParameter("bookid");
		DataBase db=new DataBase();
		if(user!=null)
		{
			db.modifyUser(user.GetId(), user.GetUserName(), user.GetPassWord(), Double.valueOf(Remain));
		}
		db.modifyBook(bookid);
		db.close();
		System.out.println(Remain);
		response.sendRedirect("MainWindow.jsp");
	}
}
