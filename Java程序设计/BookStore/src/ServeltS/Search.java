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
 * Servlet implementation class Search
 */

@WebServlet("/Search")
public class Search extends HttpServlet {
	private static final long serialVersionUID = 1L;      
    public Search() {
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
		DataBase database=new DataBase();	
		
		boolean[] Checked=new boolean[4];
		for(int i=0;i<4;i++) {
			Checked[i]=true;
		}
		String SearchText=request.getParameter("SearchText");	
		Vector<String> TypeS=new Vector<String>();
		if(request.getParameter("Type1")!=null) {
			TypeS.add("cs");
			Checked[0]=true;
			System.out.println("1");
		}
		else {
			Checked[0]=false;
		}
		if(request.getParameter("Type2")!=null) {
			TypeS.add("novel");
			Checked[1]=true;
			System.out.println("2");
		}
		else {
			Checked[1]=false;
		}
		if(request.getParameter("Type3")!=null) {
			TypeS.add("science");
			Checked[2]=true;
			System.out.println("3");
		}
		else {
			Checked[2]=false;
		}
		if(request.getParameter("Type4")!=null) {
			TypeS.add("literature");
			Checked[3]=true;
			System.out.println("4");
		}
		else {
			Checked[3]=false;
		}
		
		session.setAttribute("Checked", Checked);
		
		Integer Index=(Integer)session.getAttribute("Index");
		session.setAttribute("Types", TypeS);
		session.setAttribute("SearchText", SearchText);
		Index=1;
		Vector<Book> BookS=database.groupSearch(TypeS,SearchText, Index, 6);	
		session.setAttribute("Index", Index);
		session.setAttribute("Result", BookS);
		
		int mindex=(int)session.getAttribute("Mindex");
		mindex=1;
		session.setAttribute("Mindex", mindex);
		/*
		try {
			RequestDispatcher rd=getServletContext().getRequestDispatcher("/Search.jsp");	
			rd.forward(request, response);
		} catch (ServletException e) {
			System.out.println("Search Wrong!");
		}	
		*/
		database.close();
		response.sendRedirect("Search.jsp");
	}

}









