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


void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  //SETUP
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

}

void loop() {

 Ethernet.maintain();
}
