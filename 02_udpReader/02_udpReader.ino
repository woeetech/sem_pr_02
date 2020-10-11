
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>



byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168,2,100);

unsigned int localPort = 50000;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char  ReplyBuffer[] = "acknowledged"; 

EthernetUDP Udp;



void setup() {
 
  Serial.println("Trying to obtain IP from DHCP...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed!");
    Ethernet.begin(mac, ip);
  }
  Serial.begin(9600);
}

void loop() {
 int packetSize = Udp.parsePacket();
 if (packetSize) {
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

    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
 }
  delay(10);
  Ethernet.maintain();
}
