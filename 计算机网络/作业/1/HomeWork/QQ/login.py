#coding:utf-8
from Tkinter import *
from socket import *
from Sign import *
import Sign
class Login(Frame):
    def SuccessLoginIn(self):
        self.Success[0]=1;
    def ReturnMessage(self):
        return self.Success
    def SignIn(self):
        root=Tk()
        signTk=SignIn(root,self.udpCliSock)
        signTk.mainloop()
        
    def SendMessage(self):
        Data_Account=self.Text_Account.get('0.0', END)
        Data_PassWord=self.Text_PassWord.get('0.0', END)
        Data_Account=Data_Account[0:len(Data_Account)-1]
        Data_PassWord=Data_PassWord[0:len(Data_PassWord)-1]
        message="02#"+Data_Account+"#"+Data_PassWord+"#"
        self.udpCliSock.sendto(message, self.ADDR)       
        data, addr = self.udpCliSock.recvfrom(1024)
            
        if(data=="02:01"):
            #登录成功
            self.SuccessLoginIn()      
            self.master.destroy()
        elif(data=="02:02"):
            #密码错误
            Window_Wrong_PassWord = Toplevel(self.master)
            Window_Wrong_PassWord.title("Wrong!")
            Window_Wrong_PassWord.minsize(width=300, height=100)
            Wrong_label =Label(Window_Wrong_PassWord, text="Wrong PassWord!")
            Wrong_label.pack()
            Yes_button = Button(Window_Wrong_PassWord, text="Yes", command=Window_Wrong_PassWord.destroy)
            Yes_button.pack()
            self.Text_PassWord.delete('0.0', END)
        elif(data=="02:03"):
            #用户不存在
            Window_Wrong_PassWord = Toplevel(self.master)
            Window_Wrong_PassWord.title("Wrong!")
            Window_Wrong_PassWord.minsize(width=300, height=100)
            Wrong_label =Label(Window_Wrong_PassWord, text="This user is not exist!")
            Wrong_label.pack()
            Yes_button = Button(Window_Wrong_PassWord, text="Yes", command=Window_Wrong_PassWord.destroy)
            Yes_button.pack()
        elif(data=="02:04"):
            #用户已登录
            self.Success[0]=3
            Window_Wrong_PassWord = Toplevel(self.master)
            Window_Wrong_PassWord.title("Wrong!")
            Window_Wrong_PassWord.minsize(width=300, height=100)
            Wrong_label =Label(Window_Wrong_PassWord, text="This user has LogIn")
            Wrong_label.pack()
            Yes_button = Button(Window_Wrong_PassWord, text="Yes", command=Window_Wrong_PassWord.destroy)
            Yes_button.pack()

             
                   
    def __init__(self,master,clisock= socket(AF_INET, SOCK_DGRAM),success=[0,1]):
        #构造
        Frame.__init__(self, master, padx=10, pady=10)   
        master.title("QQ")
        master.minsize(width=500, height=200)
        self.pack()        
        #UDP
        self.ADDR = ('202.114.196.97', 21568)
        self.udpCliSock = clisock     
        #元素
        self.Text_Account = Text(self,width=30,height=2)
        self.Text_PassWord = Text(self,width=30,height=2)
        self.label_Account=Label(self,width=10,height=2,text="Account")
        self.label_PassWord=Label(self,width=10,height=2,text="PassWord")
        self.Button_Confirm = Button(self, text="Confirm", command=self.SendMessage)
        self.Button_SignIn = Button(self, text="SignIn", command=self.SignIn)
        #加入对话框
        self.Text_Account.pack()
        self.Text_PassWord.pack()
        self.label_Account.pack()
        self.label_PassWord.pack()
        self.Button_Confirm.pack()
        self.Button_SignIn.pack()
        #布局
        self.label_Account.grid(row=1,column=0,padx=1, pady=1)
        self.label_PassWord.grid(row=2,column=0,padx=1, pady=1)
        self.Text_Account.grid(row=1,column=1,padx=1, pady=1)
        self.Text_PassWord.grid(row=2,column=1,padx=1, pady=1)
        self.Button_Confirm.grid(row=3,column=1,padx=1, pady=1)
        self.Button_SignIn.grid(row=3,column=2,padx=0, pady=0)
        #成员函数
        self.Success=success

#root = Tk()
#app=Login(root)
#app.mainloop() 


        
