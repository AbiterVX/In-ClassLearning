import threading
from socket import *

ADDR = ('' , 21568) 
udpSerSock = socket(AF_INET,SOCK_DGRAM) 
udpSerSock.bind(ADDR)

while True:
    data, addr = udpSerSock.recvfrom(1024)
    print data
    if(data =="END"):
        break
    data = raw_input('> ')
    udpSerSock.sendto(data, addr) 
udpSerSock.close()


