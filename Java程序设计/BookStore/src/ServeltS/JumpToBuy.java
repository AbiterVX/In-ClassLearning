package ServeltS;

import java.io.IOException;
import java.util.Vector;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import Basics.Book;
import Basics.DataBase;

/**
 * Servlet implementation class JumpToBuy
 */
@WebServlet("/JumpToBuy")
public class JumpToBuy extends HttpServlet {
	private static final long serialVersionUID = 1L;           
    public JumpToBuy() {
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
		String bookid=request.getParameter("BookId");
		String bookPrice=request.getParameter("BookPrice");
		Book book=new Book(bookid,"none",Double.valueOf(bookPrice),"none","none",0);
		session.setAttribute("CurrentBook", book);
		int mindex=(int)session.getAttribute("Mindex");
		mindex=1;
		session.setAttribute("Mindex", mindex);
		RequestDispatcher rd=getServletContext().getRequestDispatcher("/BuyBook.jsp");
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}
	}
}
