package Basics;

import java.sql.*;
import java.util.Vector;

/***
 * #Book书的实体类
 */

public class Book {
/*--------------------------------------属性---------------------------------------*/
	private String id;  			//书的标识
	private String name;     		// #书的名字
	private double price;   		//#书的价钱
	private String type;   			//#书的类别
	private String picture_path; 	//#书的图片的相对路径
	private int sales_volume;		//销量
/*--------------------------------------方法---------------------------------------*/
	public Book(ResultSet resultset){		
		try {
			id=resultset.getString(1);
			name=resultset.getString(2);
			price=resultset.getDouble(3);
			type=resultset.getString(4);
			picture_path=resultset.getString(5);
			sales_volume=resultset.getInt(6);
		} catch (SQLException e) {
			System.out.println("Book的ResultSet构造错误");
			//e.printStackTrace();
		}		
	}
	public Book(String TheBookId,String TheBookName,double ThePrice,String TheType,String ThePicture,int TheVolume){
		id=TheBookId;
		name=TheBookName;
		price=ThePrice;
		type=TheType;
		picture_path=ThePicture;
		sales_volume=TheVolume;
	}	
	
/*--------------------------------------得到信息-----------------------------------*/	
	public String GetId(){
		return id;
	}
	public String GetName(){
		return name;
	}
	public double GetPrice(){
		return price;
	}
	public String GetType(){
		return type;
	}
	public String GetPicturePath(){
		return picture_path;
	}
	public int GetSalesVolume(){
		return sales_volume;
	}
/*--------------------------------------重置book信息-------------------------------*/	
	public void SetId(String TheId){
		id=TheId;
	}	
	public void SetName(String TheName){
		name=TheName;
	}	
	public void SetPrice(double ThePrice){	
		price=ThePrice;
	}	
	public void SetType(String TheType){
		type=TheType;
	}
	public void SetPicturePath(String ThePicture){
		picture_path=ThePicture;
	}		
	public void SetSalesVolume(int TheSalesVolume){
		sales_volume=TheSalesVolume;
	}	
}

























