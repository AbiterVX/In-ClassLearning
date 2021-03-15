from sim.api import *
from sim.basics import *


'''
Create your RIP router in this file.
'''
class RIPRouter (Entity):
    def __init__(self):               
        self.Map=[]         #The table
        self.PortS=[]       #PortS
        self.NeighbourS=[]  #Column
        self.OtherS=[]      #Row
        
    def handle_rx (self, packet, port):
        packet.ttl-=1
       
        if(isinstance(packet,DiscoveryPacket)):                                  #discover
            if packet.ttl>0:
                if not packet.is_link_up :
                    OtherIndex=self.OtherS.index(packet.src)
                    NeighbourIndex=self.NeighbourS.index(packet.src)
                    for i in self.Map:
                        i[NeighbourIndex]=21                                   
                else:    
                    if packet.src not in self.NeighbourS:
                        NewList=[]                         #empty Row
                        self.Map.append(NewList)           #add a New Row                
                        self.PortS.append(port)            #add port
                        self.NeighbourS.append(packet.src) #add neighbour
                        self.OtherS.append(packet.src)     #add another switch
                    
                        Length=len(self.NeighbourS)        #Map
                        for i in self.Map:
                            while(len(i)<Length):
                                i.append(21)
                        self.Map[-1][-1]=1
                    else:
                        self.Map[self.OtherS.index(packet.src)][self.NeighbourS.index(packet.src)]=1
                Count=0                           
                CurrentPacket=RoutingUpdate()               
                for Row in self.Map:
                    Min=21                    
                    for CurrentLength in Row:
                        if Min>CurrentLength:
                            Min=CurrentLength                       
                    CurrentPacket.add_destination(self.OtherS[Count],Min)
                    Count+=1

                if not packet.is_link_up :
                    self.send(CurrentPacket, port, flood=True)                              
                else:
                    self.send(CurrentPacket, None, flood=True)   
        elif (isinstance(packet,RoutingUpdate)):                                 #RoutingPacket                      
        
            change=False
            SrcDistance=21
            SrcIndex=0
            Count=0            
           
            NextJump=self.NeighbourS.index(packet.src)
            
            List=packet.all_dests()    
            for Destination in List:
                if Destination !=self.name:
                    if Destination in self.OtherS:                   
                        CurrentLength=self.Map[self.OtherS.index(Destination)][NextJump]                  
                        if CurrentLength!=(1+packet.get_distance(Destination)) and  CurrentLength!=1:
                            self.Map[self.OtherS.index(Destination)][NextJump]=packet.get_distance(Destination)+1                                           
                            change=True                   
                    else:                       
                        NewList=[]
                        self.OtherS.append(Destination)
                        self.Map.append(NewList)
                        while(len(self.Map[-1])<len(self.NeighbourS)):
                            self.Map[-1].append(21)                                               
                        self.Map[-1][NextJump]=packet.get_distance(Destination)+1                        
                        change=True
   
            if change==True:               
                Count=0                           
                CurrentPacket=RoutingUpdate()               
                for Row in self.Map:
                    Min=21                    
                    for CurrentLength in Row:
                        if Min>CurrentLength:
                            Min=CurrentLength                       
                    CurrentPacket.add_destination(self.OtherS[Count],Min)
                    Count+=1
                    
                self.send(CurrentPacket, None, flood=True)                 

        else:                                                                    #other packet
            '''
            print "*NAME:"+self.name
            print "          ",
            for i in self.NeighbourS:
                print i,
            print "\n",
            
            Count=0
            for i in self.Map:
                print self.OtherS[Count],
                print " ",
                Count+=1
                for j in i:
                    print j,
                print "\n",
            print "\n",

            '''              
            Index=0
            Count=0
            Min=21
            Row=self.OtherS.index(packet.dst)
            for Current in self.Map[Row]:
                if Min>Current:
                    Index=Count
                    Min=Current
                Count+=1               
            if Min<21:
                CurrentPort=self.PortS[Index]           
                if packet.ttl>0:               
                    self.send(packet, CurrentPort, flood=False)            









