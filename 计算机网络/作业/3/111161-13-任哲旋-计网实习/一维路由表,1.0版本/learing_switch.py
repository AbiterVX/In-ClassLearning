from sim.api import *
from sim.basics import *
import time

'''
Create your RIP router in this file.
'''
class LearningSwitch (Entity):
    def __init__(self):        
        self.dictionary={}                                   # the table

    def handle_rx (self, packet, port):
        packet.ttl-=1
        if(self.dictionary.has_key(packet.dst)):             #the destination is in table
            if(self.dictionary.get(packet.dst)!=port):       #the destination is not the current port                           
                CurrentPort=self.dictionary[packet.dst]      #get the destination's port
                self.send(packet, CurrentPort, flood=False)  #send packet accurately           
        else:
            self.dictionary[packet.src]=port                 #record this port 
            self.send(packet, port, flood=True)              #flood the packet
            
        
        
