package ServeltS;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class JumpToRegister
 */
@WebServlet("/JumpToRegister")
public class JumpToRegister extends HttpServlet {
	private static final long serialVersionUID = 1L;
         
    public JumpToRegister() {
        super();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{
		RequestDispatcher rd=getServletContext().getRequestDispatcher("/Register.html");
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}
	}

}
