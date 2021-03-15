<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"
    import="Basics.*"
    %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Register Successful!</title>
<style type="text/css" >
.background{
	width:100%;
	height:800px;		
	background-image:url(./1.jpg);
	background-repeat:none;
	float: left;
	background-size:120% 200%;
            
    background-position: center;
    background-size: cover;
    -webkit-filter: blur(5px);
    -moz-filter: blur(5px);
    -o-filter: blur(5px);
    -ms-filter: blur(5px);
    filter: blur(5px);	
}
.main{
    text-align: center; 
    background-color: #fff;
    border-radius: 20px;
    width: 600px;
    height: 200px;
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
	//String ID="20161001924";
     User user=(User)session.getAttribute("User");
%>
<div class="background"></div>
<div class="main" style="font-size:10px">
	<div style="margin-top:20px;font-size:40px">Register Successful!</div>	
	<br></br>
	<label style="margin-top:50px;height:50px;width:150px;font-size:35px;text-align:center;color:red">Your  ID: <%=user.GetId()%> please remember !</label>	
	<br></br>
	<div><a style="font-size:30px" href="/BookStore/MainWindow.jsp">Go To Shopping !</a></div>
</div>


	
</body>
</html>