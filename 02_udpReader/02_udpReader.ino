#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

//made-up MAC address
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCD, 0xDE, 0x02
};

//if DHCP fails:
IPAddress ip(192, 168, 2, 100);
IPAddress myDns(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255,0);

//ports around 50000 and beyond are kinda safe to use
unsigned int localPort = 50000; 

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char  ReplyBuffer[] = "acknowledged"; 

EthernetUDP Udp;


void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  //<setup>
  Serial.println("Trying to obtain IP from DHCP...");
  if (Ethernet.begin(mac) == 0) {
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield not found!");
      while(true) {
        delay(1); //basically do nothing, we're done, end of story...
      }  
    }  
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable not connected!"); //never got this message, even with cable unplugged
    }
    Serial.println("Failed to obtain IP from DHCP, setting default values.");
    Ethernet.begin(mac, ip);
  }

  Serial.print("Arduino adress: ");
  Serial.println(Ethernet.localIP());
  ///<setup>

  Udp.begin(localPort);

  
}

void loop() {
  
  char reply[] = "hello everybody!";
  IPAddress broadcast(192,168,2,255);
  Udp.beginPacket(broadcast, 50000);
  Udp.write(reply);
  Udp.endPacket();

  delay(3000);
  
  /*int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  delay(10);*/
  Ethernet.maintain();
}
