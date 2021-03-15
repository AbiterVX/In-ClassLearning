<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">


<%
	String Type=(String)request.getAttribute("Type");
	if(request.getAttribute("Type")!=null){
		if(Type.equals("purchase")){
			out.print("<title>Purchase Success!</title>");
		}
		else if(Type.equals("add")){
			out.print("<title>Add Book Success!</title>");
		}
		else if(Type.equals("remove")){
			out.print("<title>Remove Book Success!</title>");
		}
		else{
			out.print("<title>NULL!</title>");
		}
	}
	else{
		Type="null";
		out.print("<title>null!</title>");
	}
%>



<style type="text/css" >
.background{
	width:100%;
	height:1000px;		
	background-image:url(./1.jpg);
	background-repeat:none;
	float: left;
	            
    background-position: center;
    background-size: cover;
    -webkit-filter: blur(5px);
    -moz-filter: blur(5px);
    -o-filter: blur(5px);
    -ms-filter: blur(5px);
    filter: blur(5px);	
}
.main{
    
    background-color: #fff;
    border-radius: 20px;
    width: 700px;
    height: 400px;
    margin: auto;
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;  
    background-color:rgba(255,255,255,0.5);
}
.content{
	position:relative;
	top: 15px;
	left:20px;
	font-size:20px;
	width:200px;
	height:50px;
	float:left;
}	
</style>
</head>
<body>

<div>
<div class="background"></div>
<div class="main" style="font-size:25px">
	<div style="font-size:40px;text-align: center; ">Result</div>	
						
	<div style="position:relative;top:5px">
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		<%
		if(Type.equals("purchase")){
			String Remain=(String)request.getAttribute("Remain");
			out.print("You have buy it Successfully.");
			out.println("<br></br>");
			out.print("And You have "+ Remain+"$ left in your wallet");
			out.println("<div class=\"content\"> <a href=\"/BookStore/MainWindow.jsp\">return to the MainWindow</a> </div>");
		}
		else if(Type.equals("add")){
			String name=request.getParameter("name");
			double price=Double.parseDouble(request.getParameter("price"));
			String type=request.getParameter("type");
			String picturepath=request.getParameter("PicturePath");
			out.print("You have add this book Successfully");
			out.print("And the information is:");
			out.println("<br></br>");
			out.print("Name:"+name+",");
			out.println("<br></br>");
			out.print("Price:"+price+",");
			out.println("<br></br>");
			out.print("Type:"+type+",");
			out.println("<br></br>");
			out.print("Picture Path:"+picturepath);
			out.println("<br></br>");
			out.println("<div class=\"content\"> <a href=\"/BookStore/AddBook.jsp\">continue to add book</a> </div>");
			out.println("<div class=\"content\"> <a href=\"/BookStore/MainWindow.jsp\">return to the MainWindow</a> </div>");
		}
		else if(Type.equals("remove")){
			String[] RemoveId=null;
			
			if(request.getParameterValues("Checked")!=null){
				RemoveId=request.getParameterValues("Checked");
				out.print("You have remove these book sucessfully.");
				out.print("And the Ids are:");
				out.println("<br></br>");
				for(String current:RemoveId){
					out.print(current+" .  ");											
				}
				
				out.println("<div class=\"content\"> <a href=\"/BookStore/RemoveBook.jsp\">continue to remove book</a> </div>");
				out.println("<div class=\"content\"> <a href=\"/BookStore/MainWindow.jsp\">return to the MainWindow</a> </div>");
			}
			else{
				out.print("You have remove none of these book sucessfully.");
			}
		}
		else{
			out.print("NULL");
		}
		%>				
	</div>
	
</div>

	
</body>
</html>