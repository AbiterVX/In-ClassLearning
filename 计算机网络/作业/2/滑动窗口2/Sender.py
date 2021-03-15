import sys
import getopt

import Checksum
import BasicSender
import time

import threading

'''
This is a skeleton sender class. Create a fantastic transport protocol here.
'''

#for i in range(0,5):
#Packet=self.make_packet(TypeS[i],order+i,MessageS[i])
#if(TypeS[i]!='end'):                                
#    self.send(Packet)
#else:
#    self.send(Packet)
#    break 
#text3.txt
sys.argv =[sys.argv[0],'-ftext3.txt','-p33122','-a127.0.0.1']

class Sender(BasicSender.BasicSender):
    def __init__(self, dest, port, filename, debug=False):
        super(Sender, self).__init__(dest, port, filename, debug)
        
    # Main sending loop.
    def start(self):
       
        order=0;        
        LastACK=""
        CurrentACK=""
        MessageS=[]
        TypeS=[]

        for i in range(0,5):
            self.ReadFile(MessageS,TypeS)                          
        TypeS[0]='start'

        for i in range(0,5):                   #send
            Packet=self.make_packet(TypeS[i],order+i,MessageS[i])
            if(TypeS[i]!='end'):                   
                self.send(Packet)                   
            else:
                self.send(Packet)
                break
        same=0
        
        while TypeS[0]!='end':
            #time.sleep(0.5)
            CurrentACK=None
            for i in range(0,5):                
                tempACK=self.receive(0.1)                    #set timeout
                if(tempACK!=None):
                    CurrentACK=tempACK
                    
            if CurrentACK!=None:
                                                 
                if(Checksum.validate_checksum(CurrentACK)):
                    if(CurrentACK!=LastACK):   #access
                        Position,CHeckNumber=self.HandleACK(CurrentACK)                            
                        Position=Position-order                       
                        LastACK=CurrentACK
                        same=0
                        for i in range(0,Position):
                            del MessageS[0]
                            del TypeS[0]                                                  
                        #print Position
                        order+=Position
                        for i in range(0,Position):                           
                            self.ReadFile(MessageS,TypeS)
                            Packet=self.make_packet(TypeS[i],order+i,MessageS[i])
                            #print order+i
                            if(TypeS[i]!='end'):                   
                                self.send(Packet)                                              
                        #print len(MessageS)
                        
                        print "recv: %s access" %CurrentACK   ###print    
                    else:#same packet
                        for i in range(0,5):
                            Packet=self.make_packet(TypeS[i],order+i,MessageS[i])                                                                                  
                            self.send(Packet)                           
                        same+=1
                        print "recv: %s same" %CurrentACK   ###print    
                else:#package damage
                    for i in range(0,5):
                        Packet=self.make_packet(TypeS[i],order+i,MessageS[i])                                                                       
                        self.send(Packet)                       
                    same+=1
                    print "recv: %s damage" %CurrentACK   ###print    
            else: #timeout   send again
                for i in range(0,5):
                    Packet=self.make_packet(TypeS[i],order+i,MessageS[i])                                  
                    self.send(Packet)                    
                same+=1
                #print "recv: %s timeout" %CurrentACK   ###print                                                   

                                       
        self.infile.close()               

        
    def ReadFile(self,MessageS,TypeS):                      #read and return messages               
        message=self.infile.read(500)
        MessageS.append(message)
        if(len(message)!=0):                
            TypeS.append('data')
        else:               
            TypeS.append('end')               
        
    def HandleACK(self,ACK):                  # divide ACK message
        Position=0
        CHeckNumber=""
        if(ACK[0:3]=='ack'):
            ACK=ACK[4:]
            divide=ACK.index('|')
            Position=int(ACK[:divide])
            CheckNumber=ACK[(divide+1):]
        return Position,CHeckNumber

    def log(self, msg):
        if self.debug:
            print msg


'''
This will be run if you run this script from the command line. You should not
change any of this; the grader may rely on the behavior here to test your
submission.
'''
if __name__ == "__main__":
    def usage():
        print "BEARS-TP Sender"
        print "-f FILE | --file=FILE The file to transfer; if empty reads from STDIN"
        print "-p PORT | --port=PORT The destination port, defaults to 33122"
        print "-a ADDRESS | --address=ADDRESS The receiver address or hostname, defaults to localhost"
        print "-d | --debug Print debug messages"
        print "-h | --help Print this usage message"

    try:
        opts, args = getopt.getopt(sys.argv[1:],
                               "f:p:a:d", ["file=", "port=", "address=", "debug="])
    except:
        usage()
        exit()

    port = 33122
    dest = "localhost"
    filename = None
    debug = False

    for o,a in opts:
        if o in ("-f", "--file="):
            filename = a
        elif o in ("-p", "--port="):
            port = int(a)
        elif o in ("-a", "--address="):
            dest = a
        elif o in ("-d", "--debug="):
            debug = True

    s = Sender(dest,port,filename,debug)
    try:
        s.start()
    except (KeyboardInterrupt, SystemExit):
        exit()
