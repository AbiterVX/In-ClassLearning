package ServeltS;

import java.io.IOException;

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
 * Servlet implementation class AddBook
 */

@WebServlet("/AddBook")
public class AddBook extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public AddBook() {
        super();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{						
		String Name=request.getParameter("name");
		double Price=Double.parseDouble(request.getParameter("price"));
		String Type=request.getParameter("type");
		String PicturePath=request.getParameter("PicturePath");
		Book book=new Book("-1",Name,Price,Type,PicturePath,0);
		DataBase db=new DataBase();
		if(db.insertBook(book))
		{
			db.close();
			RequestDispatcher rd=getServletContext().getRequestDispatcher("/Result.jsp");
			try {
				 Type="add";
				request.setAttribute("Type",Type);
									
				rd.forward(request, response);
			} catch (ServletException e) {
				e.printStackTrace();
			}
		}
		else
		{
			db.close();
			response.sendRedirect("AddBook.jsp");
		}
		//response.sendRedirect("AddBook.jsp");
		
	}

}








