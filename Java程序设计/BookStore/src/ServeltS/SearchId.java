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
 * Servlet implementation class SearchId
 */
@WebServlet("/SearchId")
public class SearchId extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public SearchId() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doSearch(request,response);
	}
    
	private void doSearch(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException  {
		// TODO Auto-generated method stub
		HttpSession session=request.getSession();
		DataBase database=new DataBase ();
		
		String Name=request.getParameter("SearchText");
		Vector<Book> BookS=new Vector<Book>();
		Book book=database.SearchBook(Name);
		if(book!=null)
		{
			BookS.addElement(book);
		}
		
		session.setAttribute("AllBook",BookS);

		RequestDispatcher rd=getServletContext().getRequestDispatcher("/RemoveBook.jsp");
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
