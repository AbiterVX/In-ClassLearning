package ServeltS;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.mysql.cj.Session;

/**
 * Servlet implementation class QuitCount
 */
public class QuitCount extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public QuitCount() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		Cookie []cookie=request.getCookies();
		for(int i=0;i<cookie.length;i++)
		{
			cookie[i].setMaxAge(0);
			response.addCookie(cookie[i]);
		}
		HttpSession session=request.getSession();
		session.removeAttribute("User");
		response.sendRedirect("MainWindow.jsp");
		/*
		RequestDispatcher rd;
		rd=getServletContext().getRequestDispatcher("/MainWindow.jsp");	
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}	
		*/
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
