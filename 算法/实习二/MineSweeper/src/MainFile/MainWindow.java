package MainFile;
import java.util.Random;
import javax.swing.*;

import java.awt.Color;
import java.awt.Font;
import java.awt.Image;
import java.awt.event.*;
import java.nio.file.Path;
import java.util.LinkedList;
import java.util.Queue;

import java.util.Calendar;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

class RANDOM{
	public int MineNumber;
	public int Width;
	public int Height;
	public int Mine[];
	private void GetMineS() {		
		int temp=0;		
		boolean finish=true;
		Random random=new Random();
		for(int i=0;i<Mine.length;) {
			Mine[i]=random.nextInt(Width*Height+1);
			if(check(Mine,Mine[i],i)) {
				i++;
			}
		}
		
		for(int i=0;i<Mine.length-1;i++) {
			finish=true;
			for(int j=0;j<Mine.length-i-1;j++) {
				if(Mine[j]>Mine[j+1]) {
					finish=false;
					temp=Mine[j];
					Mine[j]=Mine[j+1];
					Mine[j+1]=temp;
				}
			}
			if(finish) {
				break;
			}
		}
				
		for(int i=0;i<MineNumber;i++) {
			Mine[i]--;
			System.out.print(Mine[i]);
			if(i!=MineNumber-1) {
				System.out.print(",");
			}
		}
		
		System.out.print("\n");	
		System.out.print("\n");	
	}	
	private boolean check(int mine[],int current,int j) {
		for(int i=0;i<mine.length;i++) {
			if(mine[i]==current && j!=i) {
				return false;
			}
		}
		return true;
	}
	RANDOM(){
		this(10,10,10);
	}
	RANDOM(int minenumber,int width,int heigth){
		MineNumber=minenumber;		
		Width=width;
		Height=heigth;	
		Mine=new int[MineNumber];
		GetMineS();
	}	
}

class Map{
	public int MineNumber;
	public int Width;
	public int Height;
	public int Map[][];
	public int MineS[];
	private void Initialize() {		
		int Row=0;
		int Column=0;
		for(int i=0;i<MineNumber;i++) {
			Row=MineS[i]/Width;
			Column=MineS[i]%Width;
			Map[Row][Column]=-1;			
		}
		for(int i=0;i<MineNumber;i++) {
			Row=MineS[i]/Width;
			Column=MineS[i]%Width;
			
			Map[Row][Column]=-1;
            if(Row-1>=0 && Column-1>=0 && Map[Row-1][Column-1]!=-1) {        //左上
            	Map[Row-1][Column-1]++;
			}
			if(Row-1>=0 && Map[Row-1][Column]!=-1) {                         //中上
				Map[Row-1][Column]++;  
			}
			if(Row-1>=0 && Column+1<Width && Map[Row-1][Column+1]!=-1) {     //右上
				Map[Row-1][Column+1]++;
			}
			if(Column+1<Width && Map[Row][Column+1]!=-1) {                   //右中
				Map[Row][Column+1]++;
			}
			if(Row+1<Height && Column+1<Width && Map[Row+1][Column+1]!=-1) { //右下
				Map[Row+1][Column+1]++;
			}
			if(Row+1<Height && Map[Row+1][Column]!=-1) {                     //中下
				Map[Row+1][Column]++;
			}
			if(Row+1<Height && Column-1>=0 && Map[Row+1][Column-1]!=-1) {    //左下
				Map[Row+1][Column-1]++;
			}
			if(Column-1>=0 && Map[Row][Column-1]!=-1) {                      //左中
				Map[Row][Column-1]++;
			}            
		}
		
		for(int i=0;i<Height;i++) {
			for(int j=0;j<Width;j++) {
				System.out.print(Map[i][j]);
				if(Map[i][j]!=-1) {
					System.out.print(" " );
				}
				System.out.print(" " );
			}
			System.out.print("\n");
		}
	}
	Map(){
		this(10,10,10);
	}
	Map(int minenumber,int width,int heigth){
		MineNumber=minenumber;		
		Width=width;
		Height=heigth;
		Map=new int[Height][];
		for(int i=0;i<Height;i++) {
			Map[i]=new int[Width];
			for(int j=0;j<Width;j++) {
				Map[i][j]=0;
			}
		}	
		RANDOM random=new RANDOM(minenumber,width,heigth);
		MineS=new int[minenumber];
		for(int i=0;i<minenumber;i++) {
			MineS[i]=random.Mine[i];
		}
		Initialize();
	}	
}




class mainWindows extends Thread{
    static JLabel TimeLabel;
    static JLabel RemainLabel;
    static JButton Face;
	static JFrame mainwindow=new JFrame("Mine Sweeper");
	static JButton buttonS[][];
	int clicked[][];	
	boolean GameOver;
	public int MineNumber;
	public static int Width;
	public static int Height;
	public static int TheMap[][];
	private JMenuBar MenuBar;
	private JMenu Begin;
	private JMenuItem PrimaryLevel;
	private JMenuItem MediateLevel;
	private JMenuItem SeniorLevel;
	
	private void SetType(int i,int j) {
		Font font=new Font("Time New Roman",Font.BOLD,20);
		buttonS[i][j].setFont(font);
		
		if(TheMap[i][j]==-1) {					
			buttonS[i][j].setFont(null);
			ImageIcon icon=new ImageIcon(this.getClass().getResource("mine.jpg"));
			Image temp=icon.getImage().getScaledInstance(buttonS[i][j].getWidth()/5*4, buttonS[i][j].getHeight()/5*4,icon.getImage().SCALE_DEFAULT);
			icon=new ImageIcon(temp);
			buttonS[i][j].setIcon(icon);										
		}
		else if(TheMap[i][j]==1) {
			buttonS[i][j].setText(String.valueOf(TheMap[i][j]));
			buttonS[i][j].setForeground(Color.BLUE);
			buttonS[i][j].setBackground(Color.WHITE);
		}
		else if(TheMap[i][j]==2) {
			buttonS[i][j].setText(String.valueOf(TheMap[i][j]));
			buttonS[i][j].setForeground(Color.orange);
			buttonS[i][j].setBackground(Color.WHITE);
		}
		else if(TheMap[i][j]==3) {
			buttonS[i][j].setText(String.valueOf(TheMap[i][j]));
			buttonS[i][j].setForeground(Color.PINK);
			buttonS[i][j].setBackground(Color.WHITE);
		}
		else if(TheMap[i][j]==4) {
			buttonS[i][j].setText(String.valueOf(TheMap[i][j]));
			buttonS[i][j].setForeground(Color.BLACK);
			buttonS[i][j].setBackground(Color.WHITE);
		}
		else if(TheMap[i][j]!=0) {
			buttonS[i][j].setText(String.valueOf(TheMap[i][j]));
			buttonS[i][j].setForeground(Color.CYAN);
			buttonS[i][j].setBackground(Color.WHITE);
		}
		else {
			buttonS[i][j].setBackground(Color.WHITE);
		}
	}	
	private void Flood(int row,int column){
		class Point{
			Point(int X,int Y){
				x=X;
				y=Y;
			}
			public int x;
			public int y;
		}
		Queue<Point> queue=new LinkedList<Point>();
		
		int Row=row;
		int Column=column;
		Point point=new Point(Row,Column);
		queue.add(point);
		Point CurrentPoint;
		
		while(!queue.isEmpty()) {
			CurrentPoint=queue.poll();
			Row=CurrentPoint.x;
			Column=CurrentPoint.y;
			SetType(Row,Column);
			if(clicked[Row][Column]==-1) {
				Remain+=1;
			}
			clicked[Row][Column]=1;
			
			
			if(Row-1>=0 && Column-1>=0 && clicked[Row-1][Column-1]==0) {        //左上
				clicked[Row-1][Column-1]=1;
				if(TheMap[Row-1][Column-1]==0) {
					Point NewPoint=new Point(Row-1,Column-1);
					queue.add(NewPoint);
				}
				else {
					SetType(Row-1,Column-1);
				}
				
			}
			if(Row-1>=0 && clicked[Row-1][Column]==0) {                         //中上
				clicked[Row-1][Column]=1;
				if(TheMap[Row-1][Column]==0) {
					Point NewPoint=new Point(Row-1,Column);
					queue.add(NewPoint);
				}
				else {
					SetType(Row-1,Column);
				}
				
			}
			if(Row-1>=0 && Column+1<Width && clicked[Row-1][Column+1]==0) {     //右上
				clicked[Row-1][Column+1]=1;
				if(TheMap[Row-1][Column+1]==0) {
					Point NewPoint=new Point(Row-1,Column+1);
					queue.add(NewPoint);
				}
				else {
					SetType(Row-1,Column+1);
				}							
			}
			if(Column+1<Width && clicked[Row][Column+1]==0) {                   //右中
				clicked[Row][Column+1]=1;
				if(TheMap[Row][Column+1]==0) {
					Point NewPoint=new Point(Row,Column+1);
					queue.add(NewPoint);
				}
				else {
					SetType(Row,Column+1);
				}											
			}
			if(Row+1<Height && Column+1<Width && clicked[Row+1][Column+1]==0) { //右下
				clicked[Row+1][Column+1]=1;
				if(TheMap[Row+1][Column+1]==0) {
					Point NewPoint=new Point(Row+1,Column+1);
					queue.add(NewPoint);
				}
				else {
					SetType(Row+1,Column+1);
				}							
			}
			if(Row+1<Height && clicked[Row+1][Column]==0) {                     //中下
				clicked[Row+1][Column]=1;
				if(TheMap[Row+1][Column]==0) {
					Point NewPoint=new Point(Row+1,Column);
					queue.add(NewPoint);
				}
				else {
					SetType(Row+1,Column);
				}							
			}
			if(Row+1<Height && Column-1>=0 && clicked[Row+1][Column-1]==0) {    //左下
				clicked[Row+1][Column-1]=1;
				if(TheMap[Row+1][Column-1]==0) {
					Point NewPoint=new Point(Row+1,Column-1);
					queue.add(NewPoint);
				}
				else {
					SetType(Row+1,Column-1);
				}			
				
			}
			if(Column-1>=0 && clicked[Row][Column-1]==0) {                      //左中
				clicked[Row][Column-1]=1;
				if(TheMap[Row][Column-1]==0) {
					Point NewPoint=new Point(Row,Column-1);
					queue.add(NewPoint);
				}
				else {
					SetType(Row,Column-1);
				}							
			}           
		}
    }	
	private void ShowAll() {		
		for(int i=0;i<Height;i++) {
			for(int j=0;j<Width;j++) {
				if(clicked[i][j]==0) {
					SetType(i,j);
					buttonS[i][j].setBackground(Color.lightGray);
					clicked[i][j]=1;	
				}																
			}
		}
	}
	private boolean IfWin() {
		for(int i=0;i<Height;i++) {
			for(int j=0;j<Width;j++) {
				if(clicked[i][j]==-1) {
					if(TheMap[i][j]!=-1) {
						return false;
					}
				}	
				else if(clicked[i][j]==0) {
					return false;
				}				
			}
		}
		return true;
	}
	
	mainWindows(){
		this(650,840,10,10,10,60);
	}	
	mainWindows(int W,int H,int minenumber,int width,int heigth,int Size){
		BuildGame(W,H,minenumber,width,heigth,Size);					
	}
	
	private void BuildGame(int W,int H,int minenumber,int width,int heigth,int Size) {
		/*---------------------------------------*/
		Width=width;
		Height=heigth;
		MineNumber=minenumber;
		Map map=new Map(MineNumber,Width,Height);
		TheMap=null;
		TheMap=map.Map;
			
		clicked=null;
		clicked=new int[Height][];
		for(int i=0;i<Height;i++) {
			clicked[i]=new int[Width];			
		}
		
		mainwindow.setSize(W, H);
		mainwindow.setLocationRelativeTo(null);
		mainwindow.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		
		MenuBar=new JMenuBar();		
		Begin=new JMenu("开始");
		PrimaryLevel=new JMenuItem("初级");
		MediateLevel=new JMenuItem("中级");
		SeniorLevel=new JMenuItem("高级");
		PrimaryLevel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				BuildGame(650,840,10,10,10,60);
			}					
		});
		MediateLevel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				BuildGame(800,1000,40,15,15,50);
			}				
		});
		SeniorLevel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				BuildGame(1400,1050,100,30,18,45);
			}	
		});
		Begin.add(PrimaryLevel);
		Begin.add(MediateLevel);
		Begin.add(SeniorLevel);
		MenuBar.add(Begin);
		mainwindow.setJMenuBar(MenuBar);
		
		
								
		JPanel panel=new JPanel();
		panel.setLayout(null);
		
		Face=new JButton();
		Face.setBounds(270,40, 80, 80);
		ImageIcon icon=new ImageIcon(this.getClass().getResource("face.jpg"));
		Image temp=icon.getImage().getScaledInstance(Face.getWidth(), Face.getHeight(),icon.getImage().SCALE_DEFAULT);
		icon=new ImageIcon(temp);
		Face.setIcon(icon);	
		Face.addMouseListener(new MouseAdapter(){
			public void mousePressed(MouseEvent event) {
				GameOver=false;
				BuildGame(W,H,minenumber,width,heigth,Size);				
			}
		});
		panel.add(Face);
		/*---------------------------------------*/			
		TimeLabel=new JLabel("00:00:00");
		JLabel TimeLabel2=new JLabel("时间:");
		Font font=new Font("Time New Roman",Font.BOLD,30);
		TimeLabel.setFont(font);
		TimeLabel.setBounds(500,0,200,200);
		TimeLabel2.setFont(font);
		TimeLabel2.setBounds(520,0,200,100);
		panel.add(TimeLabel);
		panel.add(TimeLabel2);
				
		hour=0;
		minute=0;
		second=0;
		IsRun=true;
		/*---------------------------------------*/		
		RemainLabel=new JLabel(String.valueOf(this.MineNumber));
		JLabel RemainLabel2=new JLabel("剩余:");
		RemainLabel.setFont(font);
		RemainLabel2.setFont(font);
		
		panel.add(RemainLabel);
		panel.add(RemainLabel2);
		RemainLabel.setBounds(20,0,200,200);
		RemainLabel2.setBounds(0,0,200,100);		
		Remain=MineNumber;
		
		
		/*---------------------------------------*/
		buttonS=new JButton[Height][];
		for(int i=0;i<Height;i++) {
			buttonS[i]=new JButton[Width];
			for(int j=0;j<Width;j++) {
				final int currentRow=i;
				final int currentColumn=j;				
				buttonS[i][j]=new JButton();
				//buttonS[i][j].setPreferredSize(new Dimension(50,50));
				buttonS[i][j].setBounds(j*Size+20,i*Size+130,Size,Size);
												
				buttonS[i][j].addMouseListener(new MouseAdapter(){
					public void mousePressed(MouseEvent event) {
						if(!GameOver) {
							if(event.getButton() ==MouseEvent.BUTTON1) {
								buttonS[currentRow][currentColumn].setIcon(null);	
								if(clicked[currentRow][currentColumn]!=1) {
									if(clicked[currentRow][currentColumn]==-1) {									
										Remain+=1;
									}
									clicked[currentRow][currentColumn]=1;							
									if(TheMap[currentRow][currentColumn]!=-1) {
										if(TheMap[currentRow][currentColumn]!=0) {
											SetType(currentRow,currentColumn);
										}
										else {
											Flood(currentRow,currentColumn);
										}	
										if(IfWin()) {
											ShowAll();
											IsRun=false;
											ImageIcon icon=new ImageIcon(this.getClass().getResource("win.jpg"));
											Image temp=icon.getImage().getScaledInstance(200,100,icon.getImage().SCALE_DEFAULT);
											icon=new ImageIcon(temp);
											JOptionPane.showOptionDialog(null, null, "You Win!", JOptionPane.DEFAULT_OPTION,
													JOptionPane.INFORMATION_MESSAGE,icon , null, null);	
											GameOver=true;
											
											ImageIcon icon1=new ImageIcon(this.getClass().getResource("winface.jpg"));
											Image temp1=icon1.getImage().getScaledInstance(Face.getWidth(), Face.getHeight(),icon.getImage().SCALE_DEFAULT);
											icon1=new ImageIcon(temp1);
											Face.setIcon(icon1);	
										}
									}
									else {
										buttonS[currentRow][currentColumn].setBackground(Color.RED);
										IsRun=false;
										ShowAll();
										ImageIcon icon=new ImageIcon(this.getClass().getResource("lose.jpg"));
										Image temp=icon.getImage().getScaledInstance(300,300,icon.getImage().SCALE_DEFAULT);
										icon=new ImageIcon(temp);
										JOptionPane.showOptionDialog(null, null, "You lose!", JOptionPane.DEFAULT_OPTION,
												JOptionPane.INFORMATION_MESSAGE,icon , null, null);	
										GameOver=true;
										
										ImageIcon icon1=new ImageIcon(this.getClass().getResource("loseface.jpg"));
										Image temp1=icon1.getImage().getScaledInstance(Face.getWidth(), Face.getHeight(),icon.getImage().SCALE_DEFAULT);
										icon1=new ImageIcon(temp1);
										Face.setIcon(icon1);
									}
								}																																				
							}
							else if(event.getButton() ==MouseEvent.BUTTON3) {
								if(buttonS[currentRow][currentColumn].getIcon()==null && clicked[currentRow][currentColumn]==0) {
									buttonS[currentRow][currentColumn].setFont(null);
									ImageIcon icon=new ImageIcon(this.getClass().getResource("flag.jpg"));
									Image temp=icon.getImage().getScaledInstance(buttonS[currentRow][currentColumn].getWidth(),
									buttonS[currentRow][currentColumn].getHeight(),icon.getImage().SCALE_DEFAULT);
									icon=new ImageIcon(temp);
									buttonS[currentRow][currentColumn].setIcon(icon);
									clicked[currentRow][currentColumn]=-1;
									Remain-=1;
									RemainLabel.setText(String.valueOf(Remain));
								}
								else {
									if(clicked[currentRow][currentColumn]!=1) {
										buttonS[currentRow][currentColumn].setIcon(null);
										clicked[currentRow][currentColumn]=0;
										Remain+=1;
										RemainLabel.setText(String.valueOf(Remain));
									}
									
								}
								
								////System.out.println(clicked[currentRow][currentColumn]);
								if(IfWin()) {
									ShowAll();
									IsRun=false;
									ImageIcon icon=new ImageIcon(this.getClass().getResource("win.jpg"));
									Image temp=icon.getImage().getScaledInstance(200,100,icon.getImage().SCALE_DEFAULT);
									icon=new ImageIcon(temp);
									JOptionPane.showOptionDialog(null, null, "You Win!", JOptionPane.DEFAULT_OPTION,
											JOptionPane.INFORMATION_MESSAGE,icon, null, null);
									GameOver=true;
									
									ImageIcon icon1=new ImageIcon(this.getClass().getResource("winface.jpg"));
									Image temp1=icon1.getImage().getScaledInstance(Face.getWidth(), Face.getHeight(),icon.getImage().SCALE_DEFAULT);
									icon1=new ImageIcon(temp1);
									Face.setIcon(icon1);	
								}
								
							}
							/*System.out.print("\n");
							for(int i=0;i<Height;i++) {
								for(int j=0;j<Width;j++) {
									System.out.print(clicked[i][j]);
									if(clicked[i][j]!=-1) {
										System.out.print(" " );
									}
									System.out.print(" " );
								}
								System.out.print("\n");
							}*/
						}
						
						
					}
				});			
				panel.add(buttonS[i][j]);				
			}
		}	
		
		//Container container=mainwindow.getContentPane();						
		mainwindow.setContentPane(panel);
		mainwindow.setVisible(true);	
	}
	
	public void run() {
		TimerRun();	
	}
	
	/*-------------------------时间-----------------------*/
	private int hour;
	private int minute;
	private int second;
	private boolean IsRun;
	private void TimerRun() {
		while(true) {
			if(IsRun) {
				second+=1;
				if(second>=60) {
					second=0;
					minute+=1;
				}
				if(minute>=60) {
					minute=0;
					hour+=1;
				}
				ShowTime();
				try {
					Thread.sleep(1000);
				}catch(InterruptedException e) {
					e.printStackTrace();
				}	
			}			
		}			
	}	
	private void ShowTime() {
		String time="";
		if(hour<10) {
			time+="0";
		}
		time+=hour+":";
		if(minute<10) {
			time+="0";
		}
		time+=minute+":";
		if(second<10) {
			time+="0";
		}
		time+=second;
		
		this.TimeLabel.setText(time);
		
	}	
	/*-------------------------剩余-----------------------*/
	private int Remain;	
	private void ShowRemain() {
		this.RemainLabel.setText(String.valueOf(this.MineNumber));
		if(this.MineNumber!=10) {
			System.out.print(String.valueOf(this.MineNumber));
		}
		
	}
}




public class MainWindow {			
	public static void main(String[] args) {
		mainWindows window=new mainWindows();
		//System.out.print("1111");
		window.start();
		
	}

}















