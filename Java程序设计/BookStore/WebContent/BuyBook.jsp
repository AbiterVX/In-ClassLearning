<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"
    import="java.util.Vector,Basics.*"
    %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1;width=device-width,initial-scale=1">
<title>Buy Book</title>
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
    width: 800px;
    height: 650px;
    margin: auto;
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;  
    background-color:rgba(255,255,255,0.5);
}
	
</style>
</head>
<body>
<%	
	User user=new User("NULL","NULL","NULL",0,0.0);
	if(session.getAttribute("User")!=null){
		user=(User)session.getAttribute("User");
	}	
	Book CurrentBook=new Book("No Id","No Name",0.0,"No Type","No Path",0);
	if(session.getAttribute("CurrentBook")!=null){
		CurrentBook=(Book)session.getAttribute("CurrentBook");
	}
	String bookid=(String)session.getAttribute("bookid");
	
%>

<div class="background"></div>
<div class="main" style="top:100px;">
	<div style="text-align: center; font-size:40px;text-align: center;background-color:rgba(132,112,255,0.8);border-top-left-radius: 20px;border-top-right-radius: 20px;">Buy It Now!</div>	
	
	<div style="font-size:35px;height:80px;margin:10px;"> 
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This Book will cost you <font style="color:red"> <%=CurrentBook.GetPrice() %> </font> $. 
		And Your have  <font style="color:red"> <%=user.GetWallet() %>  </font>  $ in your wallet
	</div>	
	
	<%
		if(user.GetWallet()-CurrentBook.GetPrice()<0){
			out.print("<div style=\"text-align: center;font-size:35px;height:50px;color:red\">The balance of your wallet is not enough.</div>");	
			out.print("<div style=\"text-align: center;font-size:35px;height:50px;color:red\">Please Recharge! </div>");	
			//out.print("<img style=\"width:300px;height:300px;margin-left:250px;\" src=\"./AliPay.png\"/>");	
		}
		
	%>
	<img style="width:300px;height:300px;margin-left:250px;" src="./AliPay.png"/>
	
	<form  action=BuyBook method=post>
		<input type="hidden" name="remain" value=<%=(user.GetWallet()-CurrentBook.GetPrice()) %> ></input>	
		<input type="hidden" name="bookid" value=<%=CurrentBook.GetId() %> ></input>		
		<input  style="font-size:25px;margin-top:30px;width:120px;height:50px;font-size:30px;margin-left:340px;" type="submit" name="page" value="Confirm"> </input>		
	</form>
	
	
</div>


	
</body>
</html>










