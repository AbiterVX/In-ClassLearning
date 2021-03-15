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
 * Servlet implementation class RemoveBook
 */
@WebServlet("/RemoveBook")
public class RemoveBook extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public RemoveBook() {
        super();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{						
		String[] RemoveId=request.getParameterValues("Checked");
		HttpSession session=request.getSession();
		DataBase db=new DataBase();
		
		if(db.deleteBook(RemoveId))
		{
			RequestDispatcher rd=getServletContext().getRequestDispatcher("/Result.jsp");
			try {
				String Type="remove";
				request.setAttribute("Type",Type);
				Vector<Book> BookS=(Vector<Book>)session.getAttribute("AllBook");
				BookS=db.GetAllBook();
				session.setAttribute("AllBook", BookS);
				rd.forward(request, response);
			} catch (ServletException e) {
				e.printStackTrace();
			}
			db.close();
		}
		else
		{
			db.close();
			response.sendRedirect("RemoveBook.jsp");
		}
		//db.deleteBook(RemoveId);
		
	}

}







