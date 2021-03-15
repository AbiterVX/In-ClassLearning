# -*- coding: cp936 -*-
from Tkinter import *
from socket import *
from ScrolledText import ScrolledText
import Tkinter
import datetime
import time
import thread
import threading


class Cilent(Tkinter.Frame):
  
  def SetAccount(self,Account):   
    self.Account=Account
    self.master.title("Talking With: "+self.Account)
  def SetNewAccount(self):
    data=self.text_accountname.get('0.0', END)
    data=data[0:len(data)-1]
    self.Account=data
    self.text_msglist.insert(END, "Current Account:"+self.Account+'\n')
    #self.master.title("Talking With"+self.Account)
  def sendmessage(self):
    msgcontent = "MySelf: " + time.strftime("%Y-%m-%d %H:%M:%S",time.localtime())
    self.text_msglist.insert(END, msgcontent, 'green')         
    data=self.text_msg.get('0.0', END)
    data=data[0:len(data)-1]
    data="03#"+self.Account+"#"+data+"#"
    self.udpCliSock.sendto(data, self.ADDR)
    data, addr = self.udpCliSock.recvfrom(1024)
    if(data=="03:01"):
      self.Line="  (OnLine)"
      self.text_msglist.insert(END,"  (He is OnLine now)" +'\n', 'yellow')
    elif(data=="03:02"):
      self.Line="  (OffLine)"
      self.text_msglist.insert(END, "   (He is Off-Line now)"+'\n', 'yellow')
    else:
      self.text_msglist.insert(END, " "+data+'\n', 'yellow')
    self.text_msglist.insert(END, self.text_msg.get('0.0', END))   
    self.text_msg.delete('0.0', END)

  def OnlineRecvMessage(self):
    data="04#"+self.Account+"#"
    self.udpCliSock.sendto(data, self.ADDR)
    data, addr = self.udpCliSock.recvfrom(1024)
    if(data!="04:0"):
      data="05#"+self.Account+"#"
      self.udpCliSock.sendto(data, self.ADDR)
      data1, addr = self.udpCliSock.recvfrom(1024)
      if data1!="05:01":
        data1=data1[3:]
        msgcontent = data1 + '\n'
        self.text_msglist.insert(END, msgcontent, 'red')
      
    global timer
    timer=threading.Timer(0.5,self.OnlineRecvMessage)
    timer.start()
    
  def recvessage(self):
    data="04#"+self.Account+"#"
    self.udpCliSock.sendto(data, self.ADDR)
    data, addr = self.udpCliSock.recvfrom(1024)

    if(data!="04:0"):   
      data="05#"+self.Account+"#"
      self.udpCliSock.sendto(data, self.ADDR)
      data1, addr = self.udpCliSock.recvfrom(1024)
    
      if data1!="05:01":
        data1=data1[3:]
        msgcontent = data1 + '\n'
        self.text_msglist.insert(END, msgcontent, 'red')    
      else:
        self.text_msglist.insert(END, "No Message!"+'\n', 'red')
    else:
      self.text_msglist.insert(END, "No Message!"+'\n', 'red')
    

      
  def __init__(self,master,clisock= socket(AF_INET, SOCK_DGRAM),account="20161001234"):
    self.Account=account
    self.Line="."
    
    Tkinter.Frame.__init__(self, master, padx=10, pady=10)   
    master.title("Talking With"+self.Account)
    #创建几个frame作为容器
    self.frame_left_top   = Frame(master,width=380, height=270, bg='white')
    self.frame_left_center  = Frame(master,width=380, height=100, bg='white')
    self.frame_left_bottom  = Frame(master,width=380, height=20)
    self.frame_left_bottom1 = Frame(master,width=380, height=20)
    self.frame_right     = Frame(master,width=170, height=400, bg='white')

    self.frame_Account = Frame(master,width=380, height=20)
    self.frame_AccountName=Frame(master,width=100, height=20, bg='white')
    ##创建需要的几个元素
    self.text_msglist    = ScrolledText(self.frame_left_top,width=60, height=22)
    self.text_msg      = ScrolledText(self.frame_left_center,width=60, height=8);
    self.button_sendmsg   = Button(self.frame_left_bottom, text=unicode('发送','eucgb2312_cn'), command=self.sendmessage)   
    self.button_recvmsg   = Button(self.frame_left_bottom1, text=unicode('接收','eucgb2312_cn'), command=self.recvessage)
    
    self.button_Account   = Button(self.frame_Account, text=unicode('设置用户:','eucgb2312_cn'), command=self.SetNewAccount)
    self.text_accountname    = Text(self.frame_AccountName,)
    #UDP
    self.ADDR = ('202.114.196.97', 21568)
    self.udpCliSock = clisock
    #创建一个绿色的tag
    self.text_msglist.tag_config('green', foreground='#008B00')
    #使用grid设置各个容器位置
    self.frame_left_top.grid(row=0, column=0, padx=2, pady=5)
    self.frame_left_center.grid(row=1, column=0, padx=2, pady=5)
    self.frame_left_bottom.grid(row=2, column=0)
    self.frame_left_bottom1.grid(row=2, column=0)
    self.frame_right.grid(row=0, column=1, rowspan=3, padx=4, pady=5)

    self.frame_Account.grid(row=5, column=0, padx=0, pady=20)
    self.frame_AccountName.grid(row=5, column=0,padx=0, pady=20)   
    self.frame_left_top.grid_propagate(0)
    self.frame_left_center.grid_propagate(0)
    self.frame_left_bottom.grid_propagate(0)
    self.frame_Account.grid_propagate(0)
    self.frame_AccountName.grid_propagate(0)    
    #把元素填充进frame
    self.text_msglist.pack()
    self.text_msg.pack()
    self.button_sendmsg.grid(sticky=E)
    self.button_recvmsg.grid(sticky=E)

    self.button_Account.grid(sticky=E)
    self.text_accountname.grid()
    

    t=threading.Thread(target=self.OnlineRecvMessage)
    t.start()

    
#root = Tk()
#app=Cilent(root)
#app.SetAccount("20161001924")
#app.mainloop() 






