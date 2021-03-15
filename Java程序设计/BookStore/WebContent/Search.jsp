<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"
     import="java.io.IOException,java.sql.*,java.io.PrintWriter,javax.servlet.http.HttpServlet,Basics.*,java.util.Vector"
    %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<%
int Current=1;
if(session.getAttribute("Index")!=null){
	Current=(int)session.getAttribute("Index");
}
else{
	session.setAttribute("Index", Current);
}
%>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1; width=device-width,initial-scale=1">
<title>BookStore</title>
<style type="text/css" >
	.Page{	
		font-size:24px;	
		position:absolute;
		top:95%; 
		left:38%; 									    
		text-align:center;
		height:50px;
	}
	.Page label{   					    
		border:4px solid #f9d52b;

		height:8px;
	}
	
	
	.BackGround{							
		width:100%;
		height:1130px;		
		background-image:url(./background1.jpg);
		background-size:120% 200%;
		background-repeat:none;
	}
	
	.MainContent{ 
		border-radius: 20px;							
		position:relative;
		width:90%;
		height:1000px;
		top:3%; 
		left:5%; 
		z-index:999;		
		background-color:rgba(255,255,255,0.7); 

	}	
	.SearchPart{	
		border-radius: 20px;							
		position:relative;
		top:1%; 
		left:1%; 
	} 	
	.ContentPart{
		border-radius: 20px;
		position:relative;
		top:5px; 
		left:3%; 		
		width:45%; 
		height:190px;
		margin:10px;
		background-color:rgba(12,197,205,0.3); 
		font-size:25px;
		float:left;
	}
	.ContentPart img{
		border-radius: 35px;
		position:absolute;
		top:5px; 
		left:10px; 	
		width:120px;
		height:180px;
		font-size:20px;
	}	
	.TypeLabel{
		font-size:35px;
	}
</style>

</head>
<body>
<%
Vector<Book> numbers=(Vector<Book>)session.getAttribute("Result");
%>
	<div id="header" style="background-color:#FF7F50;">
		<%		
		Cookie [] cookie=request.getCookies();
		String username=null;
		String pd=null;
		String id=null;
		if(cookie!=null)
		{
			for(int i=0;i<cookie.length;i++)
			{
				if(cookie[i].getName().equals("username"))
				{
					username=cookie[i].getValue();
					session.setAttribute("username", username);
				}
				else if(cookie[i].getName().equals("password"))
				{
					pd=cookie[i].getValue();
					session.setAttribute("password",pd);
				}
				else if(cookie[i].getName().equals("id"))
				{
					id=cookie[i].getValue();
					session.setAttribute("id",id);
				}
			}
		}
		out.print("<div style=\"float:right;font-size:25px\">");
		out.print("<a href=\"/BookStore/MainWindow.jsp\">MainWindow   </a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
		if(id !=null)
		{
			out.print("<a href=\"/BookStore/UserSpace.jsp\">"+"User:"+username+"</a>"); 			
		}
		else
		{
			out.print("<a href=\"/BookStore/SignIn.jsp\">SignIn</a>"); 
		}		
		

		out.println("</div>");
		%>
						
		<div style="text-align:center;font-size:25px"><h1>&nbsp;BookStore</h1></div>			
	</div>
	<div class ="BackGround" id="content">	
		<div class="MainContent">		
			<div class="SearchPart">
				<form action=Search method=post >				
					<input type=text name="SearchText"  style="border-radius: 10px;width:500px;height:40px;font-size:30px"></input>
					<input type="submit" name="Button" value="search" style="border-radius: 5px;width:120px;height:50px;font-size:35px"></input>	
					<br></br>	
					<%
					boolean[] Checked=null;
					if(session.getAttribute("Checked")!=null){
						Checked=(boolean[])session.getAttribute("Checked");

					}
					else{
						Checked=new boolean[4];
						for(int i=0;i<4;i++) {
							Checked[i]=true;
						}
					}
					
					out.print("<label class=\"TypeLabel\"><input name=\"Type1\" type=\"checkbox\"  ");
					if(Checked[0]){						
						out.print("checked=\"checked\"");						
					}
					out.print("value=\"1\" style=\"width:25px;height:30px;font-size:10px\"/> Computer </label>");
										
					out.print("<label class=\"TypeLabel\"><input name=\"Type2\" type=\"checkbox\"  ");
					if(Checked[1]){
						out.print("checked=\"checked\"");	
					}
					out.print("value=\"2\" style=\"width:25px;height:30px;font-size:10px\"/> Novel </label>");
									
					out.print("<label class=\"TypeLabel\"><input name=\"Type3\" type=\"checkbox\"  ");
					if(Checked[2]){
						out.print("checked=\"checked\"");	
					}
					out.print("value=\"3\" style=\"width:25px;height:30px;font-size:10px\"/> Science </label>");
									
					out.print("<label class=\"TypeLabel\"><input name=\"Type4\" type=\"checkbox\"  ");
					if(Checked[3]){
						out.print("checked=\"checked\"");				
					}
					out.print("value=\"4\" style=\"width:25px;height:30px;font-size:10px\"/> Literature </label>");
					
					%>
				</form>
			</div>										
			<%
			int count=numbers.size();
			if(count>6){
				count=6;
			}
			User user=null;
			if(session.getAttribute("User")!=null){
				user=(User)session.getAttribute("User");
			}
			
			for(int i=0;i<count;i++){
				Book current=numbers.elementAt(i);
				out.println("<div class=\"ContentPart\">");
				out.println("<img src=\"");
				out.println(current.GetPicturePath());
				out.println("\">");  
				out.println("<div style=\"position:absolute;top:5px; left:150px;\">Name: <font color=red>");
				out.println(current.GetName());
				out.println("</font></div>");
				out.println("<div style=\"position:absolute;top:65px; left:150px;\">Price :  <font color=red>");
				out.println(current.GetPrice());
				out.println("</font></div>");
				out.println("<div style=\"position:absolute;top:105px; left:150px;\">Sales volume :<font color=red>");
				out.println(current.GetSalesVolume());				
				out.println("</font></div>");
			    				
				if(user!=null){
					out.println("<div style=\"position:absolute;top:145px; left:150px;\"><form id=\"AddToCart\" action=AddToCart method=post>");	
					out.println("<input type=\"submit\" name=\"Button\" value=\"Add To Cart\"></input>");
					out.println("<input type=\"hidden\" name=\"Id\" value=\""+current.GetId() +"\">");	 			
					out.println("</input></form></div>");
										
					out.println("<div style=\"position:absolute;top:145px; left:250px;\"><form id=\"Buy\" action=JumpToBuy method=post>");	
					out.println("<input type=\"submit\" name=\"Button\" value=\"Buy It Now\"></input>");
					out.println("<input type=\"hidden\" name=\"BookPrice\" value=\""+current.GetPrice() +"\">");
					out.println("<input type=\"hidden\" name=\"Wallet\" value=\""+ user.GetWallet() +"\">");
					out.println("<input type=\"hidden\" name=\"UserId\" value=\""+user.GetId() +"\">");
					out.println("<input type=\"hidden\" name=\"BookId\" value=\""+ current.GetId() +"\">");
					out.println("</input></form></div>");	
				}
				
				out.println("</div>");
			}			
			%>
				
																								
			<div class="Page">
				<form action=PageTurning method="post">
					<input style="font-size:25px;" type="submit" name="page" value="Last">
					<input type="hidden" name="jump" value="Search" ></input>
					<label >Current:<%=Current%></label>
					<input style="font-size:25px;" type="submit" name="page" value="Next">
				</form>						
			</div>								
		</div>				
	</div>	
					
	<div id="End" style="background-color:#FF7F50;clear:both;text-align:center;"><h2>amazon.com</h2></div>		
</body>
</html>