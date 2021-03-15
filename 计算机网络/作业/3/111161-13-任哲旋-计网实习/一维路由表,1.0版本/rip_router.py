from sim.api import *
from sim.basics import *


'''
Create your RIP router in this file.
'''
class RIPRouter (Entity):
    def __init__(self):
        #self.PortS={}    # neighbour  port
        self.PathS={}    # dst        length
        self.WayS={}     # dst        port(neighbour)
        
    def handle_rx (self, packet, port):
        packet.ttl-=1
        
        if(isinstance(packet,DiscoveryPacket)):                                  #discover
            #self.PortS[packet.src]=port                      
                self.PathS[packet.src]=1
                self.WayS[packet.src]=port               
                CurrentPacket=RoutingUpdate()
                CurrentList=self.PathS.keys()
                for j in CurrentList:
                    CurrentPacket.add_destination(j,self.PathS.get(j))                    
                if packet.ttl>0:
                    self.send(CurrentPacket, port, flood=True)
                    
        elif (isinstance(packet,RoutingUpdate)):                                 #RoutingPacket           
            List=packet.all_dests()
            change=False
            for Destination in List:              
                if self.PathS.has_key(Destination):
                    CurrentLength=self.PathS.get(Destination)
                    if CurrentLength> (packet.get_distance(Destination)+self.PathS[packet.src] ):
                        self.PathS[Destination]=packet.get_distance(Destination)+self.PathS[packet.src]                       
                        self.WayS[Destination]=port
                        change=True                       
                else:
                    if Destination !=self.name:
                        self.PathS[Destination]=packet.get_distance(Destination)+self.PathS[packet.src]                      
                        self.WayS[Destination]=port
                        change=True;
            #self.PathS[self.name]=0   
            if change==True:               
                CurrentPacket=RoutingUpdate()
                CurrentList=self.PathS.keys()
                for j in CurrentList:
                    CurrentPacket.add_destination(j,self.PathS.get(j))                    
                if packet.ttl>0:
                    self.send(CurrentPacket, port, flood=True)
                    
        else:                                                                    #other packet            
            print self.name
            List=self.PathS.keys()
            for i in List:
                print i,self.PathS[i]                           
            CurrentPort=self.WayS[packet.dst]
            if packet.ttl>0:
                self.send(packet, CurrentPort, flood=False)            




















