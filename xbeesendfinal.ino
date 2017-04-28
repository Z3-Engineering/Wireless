
#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();

void setup() {
  
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  
  uint8_t data[] = {'w',',','9'};
//  uint8_t data1[] = {'H','O'};
  
  XBeeAddress64 addr64 = XBeeAddress64();
  addr64.setMsb(0x0013A200);//XXXXX -> Msb address of router/end node
  //addr64.setLsb(0x40C1430D);//XXXXX -> Lsb address of router/end node 

//  XBeeAddress64 addr641 = XBeeAddress64();
//  addr641.setMsb(0x0013A200);
   addr64.setLsb(0x4079E74A);
  
  ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
//  ZBTxRequest zbTx1 = ZBTxRequest(addr641, data1, sizeof(data1));
//  
  xbee.send(zbTx);
//  xbee.send(zbTx1);
  delay(1000);
  
}

