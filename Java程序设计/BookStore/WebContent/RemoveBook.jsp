<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"
    import="java.util.Vector,Basics.*"
    %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<jsp:include page="/GetAllBook"></jsp:include>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1; width=device-width,initial-scale=1">
<title>Remove Book</title>
<style type="text/css" >
.background{
	width:100%;
	height:1000px;		
	background-image:url(./1.jpg);
	background-repeat:none;	            
    background-position: center;
    background-size: cover;
}
.main{
    background-color: #fff;
    border-radius: 20px;
    width: 90%;
    height: 1000px;
    position:absolute;
    top: 5%;
    left: 5%;
    right: 0;
    bottom: 0;  
    background-color:rgba(255,255,255,0.5);
}
.SearchPart{
	font-size:20px;
	border-radius: 20px;							
	position:relative;	
	top:1%; 
	left:5%; 
} 	
.Table{
	table-layout:fixed;
	word-break:break-all;
	position:absolute;	
	top:100px; 
	left:1%;
	width:98%;
}	
.Table th{
	width:5%;
	height:100px;
}


</style>
</head>
<body>
<%
Vector<Book> BookS=new Vector<Book>();
if(session.getAttribute("AllBook")!=null){
	BookS=(Vector<Book>)session.getAttribute("AllBook");
}
else{	
	BookS.add(new Book("8","Java",36,"1","D:\\eclipse_workspace\\BookStore\\WebContent\\picture\\8.png",0));
	BookS.add(new Book("9","Computer Graphics",5,"1","D:\\eclipse_workspace\\BookStore\\WebContent\\picture\\9.png",0));
	BookS.add(new Book("10","Algorithm design and Practice",38,"1","D:\\eclipse_workspace\\BookStore\\WebContent\\picture\\10.png",0));
	BookS.add(new Book("10","Algorithm design and Practice",38,"1","D:\\eclipse_workspace\\BookStore\\WebContent\\picture\\10.png",0));
}

%>

<div>
<div class="background"></div>
<div class="main" style="font-size:25px">
	<div style="font-size:40px;text-align: center;background-color:rgba(132,112,255,0.8);border-top-left-radius: 20px;border-top-right-radius: 20px;"> <font >Remove Book</font> </div>	
		<div class="SearchPart">
			<form action=SearchId method=post >				
				<input type=text name="SearchText"  placeholder="Book Id" style="border-radius: 10px;width:200px;height:30px;font-size:20px;float:left"></input>
				<input type="submit" name="Button" value="Search" style="border-radius: 5px;margin-left:20px;width:120px;height:40px;font-size:25px;float:left"></input>						
			</form>	
			
			
		</div>		
	
	<form action=RemoveBook method=post>		
					<div style="float:left;"> 
						<input type="submit" name="Remove" value="Remove" style="float:left;margin-left:100px;margin-top:10px;width:120px;height:40px;font-size:25px"></input>
					</div>										
					<div class="Table">													
					<table border="3" rules="all" >
				 	<tr>
   					<th>ID</th>
    				<th style="width:15%;table-layout:fixed;word-break:break-all;">Name</th>
    				<th>Price</th>
    				<th>Type</th>
    				<th style="width:30%;table-layout:fixed;word-break:break-all;">Picture Path</th>
    				<th>Sales Volume</th>
    				<th>Checked</th>
  					</tr>
  					 	  					 	  					 	  					  						  								
  					<%
  					for(Book Current:BookS){
  						out.print("<tr>");
  	  					out.print("<th>"+Current.GetId()+"</th>");
  	  					out.print("<th>"+Current.GetName()+"</th>");
  	  					out.print("<th>"+Current.GetPrice()+"</th>"); 					
  	  					out.print("<th>"+Current.GetType()+"</th>");
  	  					out.print("<th style=\"width:30%\">"+Current.GetPicturePath()+"</th>");
  	  					out.print("<th>"+Current.GetSalesVolume()+"</th>");
  	  					out.print("<th>");
  	  					
  	  					out.print("<input style=\"width:25px;height:25px;\" type=\"checkbox\" name=\"Checked\" value="+Current.GetId()+"></input>");
  	  					out.print("</th>");
  	  					out.print("</tr>");
  					}  					 							
  					%>
  					
  					</div>					
  					</form>			
				
				</table>						
			</form>
	</div>
</div>

	
</body>
</html>