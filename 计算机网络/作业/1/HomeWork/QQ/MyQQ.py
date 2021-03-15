#import cilent
from Tkinter import *
from socket import *
import login
import MainWindow


ADDR = ('202.114.196.97', 21568)
udpCliSock = socket(AF_INET, SOCK_DGRAM)

Success_Login=[0,1]
root = Tk()
app=login.Login(root,udpCliSock,Success_Login)
app.mainloop()
print Success_Login[0]

if(Success_Login[0] ==1):
    root=Tk()
    app=MainWindow.MyApp(root,udpCliSock)
    app.mainloop()


data="06#"
udpCliSock.sendto(data, ADDR)
data1,addr =udpCliSock.recvfrom(1024)
