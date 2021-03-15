
import sys
import socket
import getopt

import Checksum
import BasicSender

'''
This is an unreliable sender class that reads from a file or STDIN.
'''

#sys.argv =[sys.argv[0],'--help']
sys.argv =[sys.argv[0],'-ftext3.txt','-p33122','-a127.0.0.1']
class UnreliableSender(BasicSender.BasicSender):
    # Handles a response from the receiver.
    def handle_response(self,response_packet):
        if Checksum.validate_checksum(response_packet):
            print "recv: %s" % response_packet
        else:
            print "recv: %s <--- CHECKSUM FAILED" % response_packet

    def HandleACK(self,ACK):                  # divide ACK message
        Position=0
        CHeckNumber=""
        if(ACK[0:3]=='ack'):
            ACK=ACK[4:]
            divide=ACK.index('|')
            Position=int(ACK[:divide])
            CheckNumber=ACK[(divide+1):]
        return Position,CHeckNumber
    
    # Main sending loop.
    def start(self):
        seqno = 0
        msg = self.infile.read(500)
        msg_type = None
        LastACK=""
        while not msg_type == 'end':
            next_msg = self.infile.read(500)

            msg_type = 'data'
            if seqno == 0:
                msg_type = 'start'
            elif next_msg == "":
                msg_type = 'end'

            packet = self.make_packet(msg_type,seqno,msg)
            self.send(packet)
            #print "sent: %s" % packet

            CurrentACK = self.receive()
            print "recv: %s" %CurrentACK   ###print
            if CurrentACK!=None:                                                        
                if(Checksum.validate_checksum(CurrentACK)):
                    if(CurrentACK!=LastACK):#access
                        Position,CHeckNumber=self.HandleACK(CurrentACK)                            
                        Position=Position-seqno-1                          
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
           

            msg = next_msg
            seqno += 1

        self.infile.close()

    
'''
This will be run if you run this script from the command line. You should not
need to change any of this.
'''
if __name__ == "__main__":
    def usage():
        print "BEARS-TP Unreliable Sender"
        print "Sends data unreliably from a file or STDIN."
        print "-f FILE | --file=FILE The file to transfer; if empty reads from STDIN"
        print "-p PORT | --port=PORT The destination port, defaults to 33122"
        print "-a ADDRESS | --address=ADDRESS The receiver address or hostname, defaults to localhost"
        print "-h | --help Print this usage message"

    try:
        opts, args = getopt.getopt(sys.argv[1:],
                               "f:p:a:", ["file=", "port=", "address="])
    except:
        usage()
        exit()

    port = 33122
    dest = "localhost"
    filename = None

    for o,a in opts:
        if o in ("-f", "--file="):
            filename = a
        elif o in ("-p", "--port="):
            port = int(a)
        elif o in ("-a", "--address="):
            dest = a
        print filename
        print dest
        print port
    s = UnreliableSender(dest,port,filename)
    try:
        s.start()
    except (KeyboardInterrupt, SystemExit):
        exit()




