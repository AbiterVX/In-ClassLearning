<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"
    import="java.util.Vector,Basics.*"
    %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Modify Information</title>
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
    text-align: center; 
    background-color: #fff;
    border-radius: 20px;
    width: 600px;
    height: 300px;
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

<%	
	User user=new User("NULL","NULL","NULL",0,0.0);
	if(session.getAttribute("User")!=null){
		user=(User)session.getAttribute("User");
	}
	out.println("<title>"+user.GetUserName()+"'s Space"+"</title>");
	
%>

<div>
<div class="background"></div>
<div class="main" style="font-size:25px">
	<div style="font-size:40px">Modify Information</div>	
		
	<form  action=ModifyInformation method=post>			
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">Name</label>
		<input style="height:30px;width:300px;font-size:25px;float:left" type=text placeholder="Name" name="Name" value=<%=user.GetUserName() %>></input></div>
		<br></br>
		
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">Pass Word</label>
		<input style="height:30px;width:300px;font-size:25px;float:left" type=password placeholder="Pass Word" name="PassWord" value=<%=user.GetPassWord() %>></input></div>
		<br></br>		
		
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">Wallet</label>
		<input style="height:30px;width:300px;font-size:25px;float:left" type=text placeholder="Wallet" name="Wallet" value=<%=user.GetWallet() %>></input></div>
		<br></br>	
		
		<input type=hidden name="Id"  value=<%=user.GetId() %> ></input>	
									
		<div style="position:relative;top:5px"><input style="height:40px;width:140px;font-size:25px" type="submit" name="Button" value="Modify"></input></div>				
	</form>
		
	</div>
</div>

	
</body>
</html>


