package Basics;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Vector;


/***
 * user类负责管理普通用户的操作，属性
 */

public class User 
{
/*--------------------------------------属性---------------------------------------*/
	private String user_id;           	//用户的唯一标识
	private String user_name;    		//用户的用户名
	private String pass_word;    		//用户的密码
	private int user_type;				//用户类型
	private double wallet;       		//钱包
	
	//private Vector shopping_cart;		//记录该名用户的购物车信息，记录书的标号
	//private Vector history;      		//记录已经买的书的标号
/*--------------------------------------方法---------------------------------------*/
	public User(ResultSet resultset) {
		try {
			user_id=resultset.getString(1);
			user_name=resultset.getString(2);
			pass_word=resultset.getString(3);
			user_type=resultset.getInt(4);
			wallet=resultset.getDouble(5);
		} catch (SQLException e) {
			System.out.println("User的ResultSet构造错误");
			//e.printStackTrace();
		}	
	}
	public User(String TheUserId,String TheUserName,String ThePassWord,int TheUserType,double TheWallet){
		user_id=TheUserId; 
		user_name=TheUserName; 	
		pass_word=ThePassWord;
		user_type=TheUserType;
		wallet=TheWallet; 	
	}
	
/*--------------------------------------得到信息-----------------------------------*/
	public String GetId(){
		return user_id;
	}
	public String GetUserName(){
		return user_name;
	}
	public String GetPassWord(){
		return pass_word;
	}
	public int GetUserType(){
		return user_type;
	}	
	public double GetWallet(){
		return wallet;
	}
	
/*--------------------------------------重置用户信息-------------------------------*/	
	public void SetUserId(String TheUserName){
		user_id=TheUserName;
	}
	public void SetUserName(String TheUserName){
		user_name=TheUserName;
	}
	public void SetPassWord(String ThePassWord){
		pass_word=ThePassWord;
	}	
	public void SetUserType(short TheUserType){
		user_type=TheUserType;
	}	
	public void SetWallet(double TheWallet){
		wallet=TheWallet;
	}		

}

















































