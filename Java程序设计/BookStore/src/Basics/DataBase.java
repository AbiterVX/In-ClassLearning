package Basics;

import java.sql.*;
import java.util.*;


//import com.sun.xml.internal.ws.org.objectweb.asm.Type;
public class DataBase {
     String url="jdbc:mysql://localhost:3306/book_store ? serverTimezone = GMT";//book_store is my database name
     String user="root";//username
     String password="13648615908w2b";//password
     String dirver="com.mysql.cj.jdbc.Driver";
     Connection connection;
     Statement topf;
     public DataBase()
     {
    	 try
    	 {
    		 Class.forName(dirver);
    		 connection=DriverManager.getConnection(url,user,password);
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("get database error !");
    		 e.printStackTrace();
    	 }
    	 
     }
     public Vector<Book> Search_ShopCart(String id)
     {
    	 Vector<Book> ans=new Vector<Book>();
    	 try
    	 {
    		 String sql="{CALL Search_ShopCart(?)}";
    		 CallableStatement cstm=connection.prepareCall(sql);
    		 cstm.setString(1, id);
    		 ResultSet result=cstm.executeQuery();
    		 Book book;
    		 while(result.next())
    		 {
    			 book=new Book(result);
    			 ans.addElement(book);
    		 }
    		 return ans;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("search shop cart error !");
    		 return ans;
    	 }
     }
     synchronized public boolean AddToCart(String book_id,String user_id)
     {
    	 try
    	 {
    		 System.out.println(book_id);
    		 System.out.println(user_id);
    		 String sql="insert into shop_cart values(?,?)";
    		 PreparedStatement state=connection.prepareStatement(sql);
    		 state.setString(1, book_id);
    		 state.setString(2, user_id);
    		 state.execute();
    		 return true;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("add to cart error !");
    		 return false;
    	 }
     }
     synchronized public User Register(User user)
     {
    	 try
    	 {
    		 String sql="{CALL new_User(?,?,?,?,?)}";
    		 CallableStatement cstm=connection.prepareCall(sql);
    		 cstm.registerOutParameter(1, Types.VARCHAR);
    		 cstm.setString(2, user.GetUserName());
    		 cstm.setString(3, user.GetPassWord());
    		 cstm.setInt(4, user.GetUserType());
    		 cstm.setDouble(5, user.GetWallet());
    		 cstm.execute();
    		 user.SetUserId(cstm.getString(1));
    		 return user;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("register error !");
    		 return null;
    	 }
     }
     public User SignIn(String id)
     {
    	 try
    	 {
    		 String sql="select * from user where user_id=?";
        	 PreparedStatement search_user=connection.prepareStatement(sql);
        	 search_user.setString(1, id);
        	 ResultSet result=search_user.executeQuery();
    		 //String sql="select * from user where user_id=\"1\"";
    		// Statement state=connection.createStatement();
    		// ResultSet result=state.executeQuery(sql);
        	 User user=null;
        	if(result.next()) {
        		 user=new User(result);
        		 System.out.println("find user !");
        		 System.out.println(user.GetUserName());
        	}
        	 return user;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("search user error !");
    		 return null;
    	 }
     }
     String CreateText(StringBuilder str)
     {
    	 for(int i=0;i<str.length();i++)
    	 {
    		 if(str.charAt(i)=='+')
    		 {
    			 str.deleteCharAt(i);
    			 str.insert(i, "plus");
    		 }
    		 else if(str.charAt(i)=='#')
    		 {
    			 str.deleteCharAt(i);
    			 str.insert(i, "sharp");
    		 }
    	 }
    	 StringBuilder ans=new StringBuilder("match(bookname) against");
    	 ans.append("(\""+str.toString()+"\")");
    	 return ans.toString();
     }
     String CreateType(Vector<String>arrays)
     {
    	 StringBuilder str=new StringBuilder("");
    	 for(int i=0;i<arrays.size()-1;i++)
    	 {
    		 str.append("type='"+arrays.elementAt(i)+"' or ");
    	 }	 
    	 str.append("type='"+arrays.elementAt(arrays.size()-1)+"'");
    	 
    	 System.out.println(str.toString());
    	 return str.toString();
     }
     public String CreateSearchSql(Vector<String>arrays,String text)
     {
    	 
    	 StringBuilder ans=new StringBuilder("");
    	 if(text.length()!=0)
    	 {
    		 ans.append(CreateText(new StringBuilder(text)));
    	 }
    	 
    	 if(arrays !=null && arrays.size()!=0)
    	 {
    		 if(ans.length()!=0)
    			 ans.append(" and ("+CreateType(arrays)+")");
    		 else
    			 ans.append(CreateType(arrays));
    	 }
    	 
    	 return ans.toString();
     }
     public Vector<Book> groupSearch(Vector<String>arrays,String text,int index,int num)
     {
    	 try
    	 {
    		 if(text.length()==0 && arrays.size()==0)
        	 {
        		 return nextPage(index,num);
        	 }
    		 
    		 for(int i=0;i<arrays.size();i++)
    			 System.out.println(arrays.elementAt(i));
    		 String str=CreateSearchSql(arrays,text);
    		 System.out.println(str);
    		 String sql="{CALL groupSearch(?,?,?)}";
        	 CallableStatement cstm=connection.prepareCall(sql);
        	 cstm.setString(1, str);
        	 cstm.setInt(2, index);
        	 cstm.setInt(3, num);
        	 Vector<Book> ans=new Vector<Book>();
        	 ResultSet result=cstm.executeQuery();
        	 Book book;
        	 while(result.next())
        	 {
        		 book=new Book(result);
        		 System.out.println(book.GetName());
        		 ans.addElement(book);
        	 }
        	 return ans;
    	 }
    	catch(SQLException e)
    	 {
    		e.printStackTrace();
    		System.out.println("groupSearch error !");
    		return null;
    	 }
     }
     synchronized public Book SearchBook(String id)
     {
          try
          {
        	  String sql="select * from book where id=?;";
        	  PreparedStatement pstm=connection.prepareStatement(sql);
        	  pstm.setString(1, id);
        	  ResultSet result=pstm.executeQuery();
        	  Book book=null;
        	  if(result.next())
        	  {
        		  book=new Book(result);
        	  }
        	  return book;
          }
          catch(Exception e)
          {
        	  System.out.println("search book error !");
              return null;
          }
     }
     
     synchronized public boolean insertBook(Book book)
     {
    	 try
    	 {
    		 String sql="{CALL insertBook(?,?,?,?,?)}";
    		 CallableStatement cstm=connection.prepareCall(sql);
    		 cstm.setString(1, book.GetName());
    		 cstm.setDouble(2, book.GetPrice());
    		 cstm.setString(3, book.GetType());
    		 cstm.setString(4, book.GetPicturePath());
    		 cstm.setInt(5, book.GetSalesVolume());
    		 cstm.execute();
    		 return true;
    	 }
    	 catch(Exception e)
    	 {
    		 e.printStackTrace();
    		 System.out.println("insert book error !");
    		 return false;
    	 }
     }
     public Vector<Book> GetAllBook()
     {
    	 try
    	 {
    		 Vector<Book> ans=new Vector<Book>();
    		 Book book;
    		 String sql="select * from book;";
    		 Statement state=connection.createStatement();
    		 ResultSet result=state.executeQuery(sql);
    		 while(result.next())
    		 {
    			 book=new Book(result);
    			 ans.addElement(book);
    		 }
    		 return ans;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("get all book error !");
    		 return null;
    	 }
     }
     synchronized public boolean deleteBook(String []id)
     {
    	 try
    	 {
    		 connection.setAutoCommit(false);
    		 String sql="{CALL deleteBook(?)}";
    		 CallableStatement cstm=connection.prepareCall(sql);
    		 for(int i=0;i<id.length;i++)
    		 {
    			 cstm.setString(1, id[i]);
    			 cstm.addBatch();
    		 }
    		 cstm.executeBatch();
    		 connection.commit();
    		 return true;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("delete book error !");
    		 try
    		 {
    			 connection.rollback();
    		 }
    		 catch(Exception er)
    		 {
    			 System.out.println("roll back error !");
    		 }
    		 return false;
    	 }
     }
     synchronized public boolean modifyBook(String id)
     {
    	 try
    	 {
    		 String sql="{CALL buy_book(?)}";
    		 CallableStatement cstm=connection.prepareCall(sql);
    		 cstm.setString(1, id);
    		 cstm.execute();
    		 return true;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("buy book error !");
    		 return false;
    	 }
     }
     synchronized public boolean modifyUser(String id,String username,String pd,double wallet)
     {
    	 try
    	 {
    		 String sql="{CALL updateUser(?,?,?,?)}";
    		 CallableStatement cstm=connection.prepareCall(sql);
    		 cstm.setString(1, username);
    		 cstm.setString(2, pd);
    		 cstm.setDouble(3, wallet);
    		 cstm.setString(4, id);
    		 cstm.execute();
    		 return true;
    	 }
    	 catch(Exception e)
    	 {
    		 System.out.println("modify user error !");
    		 return false;
    	 }
     }
     public Vector<Book> nextPage(Integer index,int num)
     {
    	 try
    	 {
    		 String sql= "{CALL proc(?,?)}";
 			CallableStatement cstm=connection.prepareCall(sql);
 			//*********index is 1,every page show 2 infomation
 			cstm.setInt(1, index);
 			cstm.setInt(2, num);
 			
 			ResultSet result=cstm.executeQuery();
 			Vector<Book> ans=new Vector<Book>();
 			Book b;
 			while(result.next())
 			{
 			    b=new Book(result.getString(1),result.getString(2),result.getDouble(3),result.getString(4),result.getString(5),result.getInt(6));
 			    ans.addElement(b);
 			}
 			return ans; 
    	 }
    	 catch(Exception e)
    	 {
    		 return null;
    	 }
     }
     public Vector<Book> search_top(int index,int size)
     {
    	 try
    	 {
                String sql="{CALL proc()}";
    			CallableStatement cstm=connection.prepareCall(sql);
    			ResultSet result=topf.executeQuery(sql);
    			Vector<Book> ans=new Vector<Book>();
    			Book tmp;
    			while(result.next())
    			{
    				//Book tmp=new Book(result);
    				tmp=new Book(result.getString(1),result.getString(2),result.getDouble(3),result.getString(4),result.getString(5),result.getInt(6));
    				ans.addElement(tmp);
    			}
    			return ans;
    		
    	 }
    	catch(Exception e)
    	 {
    		System.out.println("search error !");
    		return null;
    	 }
     }
     public void close()
     {
    	try
    	{
    		connection.close();
    	}
    	catch(Exception e)
    	{
    		System.out.println("close database error !");
    	}
     }
}
