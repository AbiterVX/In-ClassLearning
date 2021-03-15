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
 * Servlet implementation class PageTurning
 */
@WebServlet("/PageTurning")
public class PageTurning extends HttpServlet {
	private static final long serialVersionUID = 1L;   
    public PageTurning() {
        super();       
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{	
		String jump=request.getParameter("jump");
		if(jump.equals("MainWindow"))
		{
			HttpSession session=request.getSession();
			Integer Current=(Integer)session.getAttribute("Mindex");
			if(request.getParameter("page").equals("Last")) {
				if(Current!=1) {
					Current--;
					//BookS=database.groupSearch(TypeS,SearchText, Current, 5);	
					session.setAttribute("Mindex", Current);
				}
				else {
					//BookS=database.Search_Top();
					//session.setAttribute("Index", Current);session.setAttribute("Index", Current);
				}
			}
			else if(request.getParameter("page").equals("Next")) {	
				//Vector<Book> CurrentBook=database.groupSearch(TypeS,SearchText, Current+1, 5);
					Current++;
					session.setAttribute("Mindex", Current);	
			}	
			response.sendRedirect("MainWindow.jsp");
		}
		else if(jump.equals("Search"))
		{
			HttpSession session=request.getSession();
			DataBase database=new DataBase();
			
			Integer Current=(Integer)session.getAttribute("Index");
			Vector<Book> BookS=null;
			//String SearchText=request.getParameter("SearchText");	
			String SearchText=(String)session.getAttribute("SearchText");
			Vector<String> TypeS=(Vector<String>)session.getAttribute("Types");
			if(TypeS==null)
				TypeS=new Vector<String>();
			if(request.getParameter("page").equals("Last")) {
				if(Current!=1) {
					Current--;
					BookS=database.groupSearch(TypeS,SearchText, Current, 5);	
					session.setAttribute("Index", Current);
				}
				else {
					//BookS=database.Search_Top();
					//session.setAttribute("Index", Current);session.setAttribute("Index", Current);
				}
			}
			else if(request.getParameter("page").equals("Next")) {	
				Vector<Book> CurrentBook=database.groupSearch(TypeS,SearchText, Current+1, 5);
				if(CurrentBook!=null && CurrentBook.size()!=0 ) {
					Current++;
					BookS=CurrentBook;
					session.setAttribute("Index", Current);	
				}

				
			}	
			database.close();
			if(BookS!=null) {
				session.setAttribute("Result", BookS);
			}		
			response.sendRedirect("Search.jsp");
		}
		
		
			
	}

}













