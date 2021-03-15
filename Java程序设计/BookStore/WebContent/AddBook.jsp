<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Add Book</title>
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
    width: 500px;
    height: 350px;
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
<div>
<div class="background"></div>
<div class="main" style="font-size:25px">
	<div style="font-size:40px">Add A Book</div>	
	<form id="AddBook" action=AddBook method=post>
			
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">Name</label>
		<input style="height:30px;width:300px;font-size:25px;float:left" type=text placeholder="Book Name" name="name"></input></div>
		<br></br>
		
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">Price</label>
		<input style="height:30px;width:300px;font-size:25px;float:left" type=text placeholder="Book Price" name="price"></input></div>
		<br></br>
		
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">Type</label>
		<select name="type" style="height:30px;width:300px;font-size:25px;float:left">
 	 		<option value ="cs">Computer</option>
  			<option value ="novel">Novel</option>
  			<option value="science">Science</option>
  			<option value="literature">Literature</option>
		</select>	
		</div>
		<br></br>
		
		<div style="position:relative;top:5px">
		<label style="height:30px;width:150px;font-size:25px;float:left">PicturePath</label>
		<input style="height:30px;width:300px;font-size:25px;float:left" type=file placeholder="Picture Path" name="PicturePath"></input></div>
		<br></br>
		
							
		<div style="position:relative;top:25px"><input style="height:40px;width:140px;font-size:25px" type="submit" name="Button" value="Add"></input></div>				
	</form>



</div>
</div>

	
</body>
</html>