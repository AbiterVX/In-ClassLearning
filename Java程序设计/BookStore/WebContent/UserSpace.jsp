<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"
    import="java.util.Vector,Basics.*"
%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<%
 String id=new String("none");
Cookie []cookies=request.getCookies();
 for(int i=0;i<cookies.length;i++)
 {
	 if(cookies[i].getName().equals("id"))
	 {
		 id=cookies[i].getValue();
		 break;
	 }
 }
	 
%>
<jsp:include page="/LoadUser"><jsp:param name="id" value="<%=id%>"/></jsp:include>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1; width=device-width,initial-scale=1">
<%	
	User user=(User)session.getAttribute("User");
	if(user!=null){
		out.println("<title>"+user.GetUserName()+"'s Space"+"</title>");	
	}
	else
	{
		user=new User("None","None","None",-1,0);
		out.println("<title>"+user.GetUserName()+"'s Space"+"</title>");
	}
	
%>
<style type="text/css" >
.main{
	position:absolute;		
    background-color: #fff;
    border-radius: 20px;   
    width: 90%;
    height: 1050px;   
    top: 20px;
    left: 5%;	
    background-color:rgba(255,255,255,0.8);
}
.background{	
	width:100%;
	height:1100px;
	top: 50px;
    left: 5%;	
	background-image:url(./1.jpg);
	background-repeat:none;
	background-size:120% 200%;
            
    background-position: center;
    background-size: cover;
    -webkit-filter: blur(5px);
    -moz-filter: blur(5px);
    -o-filter: blur(5px);
    -ms-filter: blur(5px);
    filter: blur(5px);	
}
.title{
	text-align: center;
	position:relative;
	font-size:35px;
	top: 1%;
    left: 5%;
	width:90%;
	height:40px;
	background-color:#FF7F50;
}
.Information{
	border-radius: 20px;
	position:relative;
	top: 20px;
    left: 5%;   
    width:90%;
	height:125px;
	background-color:rgba(173,216,230,0.7);
}
.ShoppingCart{
	border-radius: 20px;
	position:relative;
	top: 30px;
    left: 5%; 
    width:90%;
	height:830px;
	background-color:rgba(173,216,230,0.7);
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
.goods{
	border-radius: 20px;
	position:relative;
	margin-top:10px;	
	margin-left:25px;
	font-size:20px;
	width:45%;
	height:250px;
	float:left;
	background-color:rgba(132,112,255,0.7);
}
.goods img{
		border-radius: 20px;
		position:absolute;
		top:10px; 
		left:20px; 	
		width:150px;
		height:230px;
	}	
</style>
</head>
<body>


<div>
<div class="background"></div>
<div class="main ">	
	<div class="title"><%=user.GetUserName()%>'s Space</div>
	<div class="Information">
		<div style="border-top-left-radius:20px;border-top-right-radius:20px;position:relative;font-size:25px;background-color:rgba(132,112,255,0.7);"> 
		&nbsp;&nbsp;User Information</div>
		
		
		<div class="content">ID:<font color=red><%=user.GetId() %></font></div>
		<div class="content">Name:<font color=red><%=user.GetUserName() %></font></div>
		<div class="content">Type:<font color=red><%
		if(user.GetUserType()==0){
			out.print("Ordinary User");
		}
		else{
			out.print("Administrators");
		}
		 %></font></div>
		<div class="content">Wallet:<font color=red><%=user.GetWallet() %></font></div>
	
		<%
			if(user.GetUserType()==1){
				out.println("<div class=\"content\"> <a href=\"/BookStore/AddBook.jsp\">Add Book</a> </div>");
				out.println("<div class=\"content\"> <a href=\"/BookStore/RemoveBook.jsp\">Remove Book</a> </div>");
			}
		%>
			<div class="content"> <a href="/BookStore/Modify.jsp">Modify</a> </div>
			  <div class="content"> <a href="quit?action=view">Quit This Account</a> </div>  
	</div>
	
	<div class="ShoppingCart">
		<div style="border-top-left-radius:20px;border-top-right-radius:20px;position:relative;font-size:25px;background-color:rgba(132,112,255,0.7);"> 
		&nbsp;&nbsp; Shopping Cart</div>
				
		<% 	
			Vector<Book> numbers=(Vector<Book>)session.getAttribute("ShopCart");
				
			int count=1;
			for(Book current:numbers){
				out.println("<div class=\"goods\">");
				out.println("<div class=\"ContentPart\">");
				out.println("<img src=\"./picture/");
				out.println(count+".png\">");
				out.println("<div style=\"position:absolute;top:30px; left:185px;\">Name:"); 
				out.println("<font color=red>");
				out.println(current.GetName());
				out.println("</font></div>");
				out.println("<div style=\"position:absolute;top:70px; left:185px;\">Price :");								
				out.println("<font color=red>");
				out.println(current.GetPrice());
				out.println("</font></div>");						
				out.println("<div style=\"position:absolute;top:150px; left:185px;\">Sales volume:");
				out.println("<font color=red>");
				out.println(current.GetSalesVolume());
				out.println("</font></div>");
				out.println("</div>");
				out.println("</div>");
			}	 
			
			%>
	</div>
</div>
</div>




</body>
</html>















