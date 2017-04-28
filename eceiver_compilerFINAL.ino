#include <Wire.h>
#include <Printers.h>
#include <XBee.h>
#include <Pixy.h>
#include <PixyI2C.h>
#include <PixySPI_SS.h>
#include <PixyUART.h>
#include <TPixy.h>
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <iterator>
#include <iostream>
using namespace std;
namespace std
{
  ohserialstream cout(Serial);
}

template <typename T_ty> struct TypeInfo { static const char * name; };
template <typename T_ty> const char * TypeInfo<T_ty>::name = "unknown";
#define TYPE_NAME(var) TypeInfo< typeof(var) >::name
#define MAKE_TYPE_INFO(type)  template <> const char * TypeInfo<type>::name = #type;

MAKE_TYPE_INFO (int)
MAKE_TYPE_INFO (float)
MAKE_TYPE_INFO (short)
MAKE_TYPE_INFO (double)
MAKE_TYPE_INFO (void)
MAKE_TYPE_INFO (String)
MAKE_TYPE_INFO (std::string)
int wallNumber=0;
std::basic_string<char> wall;
std::basic_string<char>A="A";
std::basic_string<char>B="B";
std::basic_string<char>C="C";
std::basic_string<char>D="D";
std::basic_string<char>W="W";
std::basic_string<char>w="w";

Pixy pixy;
XBee xbee=XBee();
XBeeResponse response=XBeeResponse();
ZBRxResponse rx=ZBRxResponse();
//=========================final code for actual experiment to run.==========================//
//============2 robots are configured to send info gathered from boundaries==================//
//=========the 3rd gathers its boundary info and saves it but does not send,=================//
//=========only receive and configure all the info and do checking etc=======================//
//=================THIS CODE IS FOR RECEIVING BOUNDARY INFO====================================// 



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
xbee.begin(Serial);
Wire.begin();
}

byte x=0;

void loop() {
  // put your main code here, to run repeatedly:

}
void geetPaket(){  
string sample;
  xbee.readPacket(); 
    if (xbee.getResponse().isAvailable()) {
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        xbee.getResponse().getZBRxResponse(rx);
        for (int i = 0; i < rx.getDataLength(); i++) {
          sample += (char)rx.getData(i);
        }
        string delimiter=",";
        size_t pos = 0;
        string token;
        while ((pos = sample.find(delimiter)) != string::npos) {
           token = sample.substr(0, pos);
           wall=token;
           sample.erase(0, pos + delimiter.length());     
           wallNumber=atoi(sample.substr(0,string::npos).c_str());
        }
    }else if (xbee.getResponse().isError()) {
      Serial.println("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
    } 
  delay(100);
  }
}

vector<int> dimensionCheck;
void dimensioner(int dim){
  dimensionCheck.push_back(dim);
}

void Listen(){
geetPaket();
  if (wall==C){ //C# denotes run wall count
   wallcount();             
     if(dimensions[0]==0){
      char k=dimensions[1];
      dimensions[1]=0;
      }
      if (dimensions[1]==0){
       char z=dimensions[0];
      dimension[1]=0;
     }
   unitmatMoveSensedForward(0,0,5,2);  // 2 is robot 2, change for each robot
   delay(1000);         // customize delay so that it moves however long it takes to rotate 90 degrees
   wallcount();
      if(dimensions[0]==0){
      char k=dimensions[1];
      dimensions[0]=0;
      }
      if (dimensions[1]==0){
       char z=dimensions[0];
      dimension[0]=0;
      }
    if (wall==x){
      dimensioner(wallNumber);
    }
    if (wall==y){
      dimensioner(wallNumber); 
    }
    for (int i=0, i<6,i+=2){
      if (dimensionCheck(i)==8){    //8 is correct dimension of whichever we set to send first
        dimensionCheck(i)==1;
      }
    }
    for (int i=1,i<6,i+=2){
      if(dimensionCheck(i)==12){  //12 is correct dimension of wichever we set to send second
        dimensionCheck(i)==1;
      }
    }
    if (dimensionCheck[0]==1&&dimensionCheck[1]==1){
      cout<<"Robot one got it right"<<endl;
    }
    if(dimensionCheck[2]==1&&dimensionCheck[3]==1){
      cout<<"Robot 2 got it right"<<endl;
    }
    if(dimensionCheck[4]==1&&dimensionCheck[5]==1){
      cout<<"Robot 3 got it right"<<endl;
    }
    uint8_t data[] = {'y',',',12};     //12 is whatever correct y dim is
    XBeeAddress64 addr64 = XBeeAddress64();
    addr64.setMsb(0x0013A200);//XXXXX -> Msb address of router/end node   (robot 1)
    addr64.setLsb(0x41555A87);//XXXXX -> Lsb address of router/end node 
    ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
    xbee.send(zbTx);
    delay(1000);
    uint8_t data[] = {'x',',',8};     //8 is whatever correct x dim is
    XBeeAddress64 addr64 = XBeeAddress64();
    addr64.setMsb(0x0013A200);//XXXXX -> Msb address of router/end node   (robot 2)
    addr64.setLsb(0x41555A87);//XXXXX -> Lsb address of router/end node 
    ZBTxRequest zbTx = ZBTxRequest(addr64, data, sizeof(data));
    xbee.send(zbTx);
    delay(1000);
    x=8;
    y=12;
      }
   }
   if (wall==R){//denotes run find resources
    findResources(); 
    //send coordinates received to the other 2 robots for water
   }
   
   }
 
 }
