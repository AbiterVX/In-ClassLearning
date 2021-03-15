import sys
import getopt

import Checksum
import BasicSender

'''
This is a skeleton sender class. Create a fantastic transport protocol here.
'''

sys.argv =[sys.argv[0],'-fREADME','-p33122','-a127.0.0.1']

class Sender(BasicSender.BasicSender):
    def __init__(self, dest, port, filename, debug=False):
        super(Sender, self).__init__(dest, port, filename, debug)
        
    # Main sending loop.
    def start(self):
        #print "asdf"
        order=0;        
        LastACK=""
        CurrentACK=""
        CurrentMessageS,CurrentTypeS=self.ReadFile()
        Length=len(CurrentMessageS)            
        CurrentTypeS[0]='start'
        end=0
        while len(CurrentMessageS)!=1 :
            #print "asdf"
            NextMessage,NextTypeS=self.ReadFile()
                                       
            for i in range(0,Length):                   #send
                Packet=self.make_packet(CurrentTypeS[i],order+i,CurrentMessageS[i])
                if(CurrentTypeS[i]!='end'):
                    self.send(Packet)
                    #print order+i
                else:
                    end=1;
                #print "sent: %s" % Packet
                           
            AccessCount=0
            while(AccessCount<Length-1-end):                          #receive
                CurrentACK=self.receive(0.5)                    #set timeout
                print "recv: %s" %CurrentACK   ###print
                if CurrentACK!=None:
                                                          
                    if(Checksum.validate_checksum(CurrentACK)):
                        if(CurrentACK!=LastACK):#access
                            Position,CHeckNumber=self.HandleACK(CurrentACK)                            
                            Position=Position-order-1                          
                            AccessCount=Position
                            LastACK=CurrentACK                                                       
                        else:#same packet                            
                            Packet=self.make_packet(CurrentTypeS[AccessCount],order+AccessCount,CurrentMessageS[AccessCount])
                            self.send(Packet)
                            #print order+AccessCount
                    else:#package damage
                        Packet=self.make_packet(CurrentTypeS[AccessCount],order+AccessCount,CurrentMessageS[AccessCount])
                        self.send(Packet)
                        #print order+AccessCount
                else: #timeout   send again
                    Packet=self.make_packet(CurrentTypeS[AccessCount],order+AccessCount,CurrentMessageS[AccessCount])
                    self.send(Packet)
                    #print order+AccessCount
            if(end==1):
                break
            Length=len(CurrentMessageS)   
            order+=Length
            CurrentMessageS=NextMessage
            CurrentTypeS=NextTypeS
            Length=len(CurrentMessageS)      
            if(Length==1 and NextTypeS[0]=='end'):
                break
                                       
        self.infile.close()               

        
    def ReadFile(self):                      #read and return messages
        MessageList=[]
        TypeList=[]
        for count in range(0,5):
            message=self.infile.read(500)
            MessageList.append(message)
            if(len(message)!=0):                
                TypeList.append('data')
            else:               
                TypeList.append('end')
                break       
        return MessageList,TypeList
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
