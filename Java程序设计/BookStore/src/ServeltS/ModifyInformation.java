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

import Basics.DataBase;
import Basics.User;

/**
 * Servlet implementation class ModifyInformation
 */
@WebServlet("/ModifyInformation")
public class ModifyInformation extends HttpServlet {
	private static final long serialVersionUID = 1L;
    public ModifyInformation() {
        super();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doSearch(request,response);
	}
	public void doSearch(HttpServletRequest request,HttpServletResponse response)throws IOException{						
		String Id=request.getParameter("Id");
		String Name=request.getParameter("Name");
		String PassWord=request.getParameter("PassWord");
		double Wallet=Double.parseDouble(request.getParameter("Wallet"));
		DataBase db=new DataBase();
		db.modifyUser(Id, Name, PassWord, Wallet);
		Cookie []cookies=request.getCookies();
		HttpSession session=request.getSession();
		User user=db.SignIn(Id);
		db.close();
		for(int i=0;i<cookies.length;i++)
		{
			if(cookies[i].getName().equals("username"))
			{
				cookies[i].setValue(Name);
				response.addCookie(cookies[i]);
				break;
			}
		}
		RequestDispatcher rd=getServletContext().getRequestDispatcher("/MainWindow.jsp");
		try {
			rd.forward(request, response);
		} catch (ServletException e) {
			e.printStackTrace();
		}
	}


}






