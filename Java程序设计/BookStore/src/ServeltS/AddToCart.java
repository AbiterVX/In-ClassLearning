package ServeltS;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import Basics.DataBase;
import Basics.User;

/**
 * Servlet implementation class AddToCart
 */
@WebServlet("/AddToCart")
public class AddToCart extends HttpServlet {
	private static final long serialVersionUID = 1L;       
    public AddToCart() {
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
		String Id=(String)request.getParameter("Id");
		User user=null;
		if((User)session.getAttribute("User")!=null) {
			user=(User)session.getAttribute("User");
			DataBase db=new DataBase ();
			if(db.AddToCart(Id, user.GetId()))
			{
				System.out.println("add succeed !");
			}
			else
			{
				System.out.println("add failed !");
			}
			db.close();
			response.sendRedirect("MainWindow.jsp");
		}
		else {
			RequestDispatcher rd=getServletContext().getRequestDispatcher("/SignIn.jsp");
			try {
				rd.forward(request, response);
			} catch (ServletException e) {
				e.printStackTrace();
			}
		}
		
		
		
		
		
	}
	
	
}










