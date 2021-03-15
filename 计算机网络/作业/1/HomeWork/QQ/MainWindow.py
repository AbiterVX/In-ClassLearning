import Tkinter
from Tkinter import *
from socket import *
import cilent


class MyApp(Tkinter.Frame):

    def Create_Cilent(self,account="20161002099"):
        root=Tkinter.Tk()    
        app=cilent.Cilent(root,self.udpCliSock)
        app.SetAccount("20161002099")

    def Create_Cilent1(self):
        root=Tkinter.Tk()    
        app=cilent.Cilent(root,self.udpCliSock)
        app.SetAccount("20161002099")
        
    def Create_Cilent2(self):       
        root=Tkinter.Tk()    
        app=cilent.Cilent(root,self.udpCliSock)
        app.SetAccount("20161001703")
        
    def Create_Cilent3(self):
        root=Tkinter.Tk()    
        app=cilent.Cilent(root,self.udpCliSock)
        app.SetAccount("20161001797")
             
    def __init__(self, master,clisock= socket(AF_INET, SOCK_DGRAM)):
        self.udpCliSock=clisock
        
        Tkinter.Frame.__init__(self, master, padx=10, pady=10)
        master.title("QQ Main Window")     
        master.minsize(width=250, height=100)
        self.pack()
               
        self.quitButton1 = Tkinter.Button(self, text="20161002099", command=self.Create_Cilent1)
        self.quitButton1.pack()
        self.quitButton2 = Tkinter.Button(self, text="20161001703", command=self.Create_Cilent2)
        self.quitButton2.pack()
        self.quitButton3 = Tkinter.Button(self, text="20161001797", command=self.Create_Cilent3)
        self.quitButton3.pack()
        self.quitButton4 = Tkinter.Button(self, text="Friend4", command=self.Create_Cilent)
        self.quitButton4.pack()
        self.quitButton11 = Tkinter.Button(self, text="Friend5", command=self.Create_Cilent)
        self.quitButton11.pack()
       
        self.quitButton = Tkinter.Button(self, text="Quit", command=self.create_quit_window)
        self.quitButton.pack()
 
    def create_quit_window(self):       
        ADDR = ('202.114.196.97', 21568)
        data="06#"
        self.udpCliSock.sendto(data, ADDR)
        data, addr = self.udpCliSock.recvfrom(1024)
        if(data=="06:01"):
            Window_Quit = Toplevel(self.master)
            Window_Quit.title("Success!")
            Window_Quit.minsize(width=400, height=100)
            Quit_label =Label(Window_Quit, text="You are off-line!")
            Quit_label.pack()
            Yes_button = Button(Window_Quit, text="Yes", command=Window_Quit.destroy)
            Yes_button.pack()
        elif(data=="06:02"):
            Window_Quit = Toplevel(self.master)
            Window_Quit.title("Error!")
            Window_Quit.minsize(width=400, height=100)
            Quit_label =Label(Window_Quit, text="You have off-line!")
            Quit_label.pack()
            Yes_button = Button(Window_Quit, text="Yes", command=Window_Quit.destroy)
            Yes_button.pack()


            
#root = Tkinter.Tk()
#app = MyApp(root)
#app.mainloop()
