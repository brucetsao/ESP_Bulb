#include <String.h>
#include "Pinset.h"
#include <WiFi.h>
String connectstr ;
String MacData ;
char Macchar[12] ;
WiFiClient client;

// Replace with your network credentials
char* APid = "BLUB123456" ;
//char APid[8] ;
char* APpwd = "12345678";
// Set web server port number to 80
WiFiServer server(80);
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?


// How many NeoPixels are attached to the Arduino?


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, WSPIN, NEO_GRB + NEO_KHZ800);


byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "      " ;
int delayval = 500; // delay for half a second
boolean readok = false ;


void setup() {
  // put your setup code here, to run once:
     initAll() ;
        Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(APid, APpwd);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
    delay(initDelayTime) ;   //wait 2 seconds
     DebugMsgln("Waiting for Wifi APPs Connection") ;
}


void loop() {
  
  // put your main code here, to run repeatedly:
  if (Serial.available() >0)
  {
    ReadStr = Serial.readStringUntil(0x23) ;    // read char # 
     //  Serial.read() ;
      DebugMsg("ReadString is :(") ;
       DebugMsg(ReadStr) ;
       DebugMsg(")\n") ;
        if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
           {
            DebugMsgln("Change RGB Led Color") ;
            ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
           }
  }
  /*
    len = wifi.recv();
    if (len >=commandlength) 
    {
          Serial.print("Wifi Received data len is :(") ;
          Serial.print(len) ;
          Serial.print(")\n") ;
    }
  if(len >=commandlength)
  {
    readok = false ;
    int i = 0 ;
    int j=0 ;
    while (i < len)
    {
      revchar =wifi.MessageBuffer[i] ;
      Serial.print(revchar);
      if (revchar == commandhead)
          {
             j= 0 ;
             recvData[j] =  revchar ;
             if ((len-i) >10)
                {
                    for(j=1 ; j<=9; j++)
                        {
                          revchar =wifi.MessageBuffer[i+j] ;
                          recvData[j] =  revchar ;
                              Serial.print(revchar);
                        }
                        revchar =wifi.MessageBuffer[i+10] ;
                        if ( revchar == commandtail) 
                            {
                                 recvData[10] = revchar ;
                                 recvData[11] = 0x00 ;
                                readok = true ;
                                break ;
                            }
                            else
                            {
                                readok = false ;
                                break ;
                            }
                }
          }
          else
          {
            i++ ;
          }
      
    }

        if (!readok) 
            {
              Serial.println("read fail") ;
              return ;
            }
            for (int i = 0 ; i<11; i++)
              {
              Serial.print("(") ;
              Serial.print(i) ;
              Serial.print("):") ;
              Serial.print("(") ;
              Serial.print(recvData[i]) ;
              Serial.print(")\n") ;
  
              }
           ReadStr = String(recvData) ;
          if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
           {
                DebugMsgln("Change RGB Led Color") ;
                ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
                wifi.Send(wifi.client_id , "OK" , 2) ;
           }
        
     */
  //------------------------------------------
  
}

void ChangeBulbColor(int r,int g,int b)
{
      // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
   for(int i=0;i<NUMPIXELS;i++)
   {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
    
       // delay(delayval); // Delay for a period of time (in milliseconds).
    }
      pixels.show(); // This sends the updated pixel color to the hardware.
}

boolean DecodeString(String INPStr, byte *r, byte *g , byte *b) 
{
                    Serial.print("check string:(") ;
                    Serial.print(INPStr) ;
                         Serial.print(")\n") ;

      int i = 0 ;
      int strsize = INPStr.length();
      for(i = 0 ; i <strsize ;i++)
          {
                    Serial.print(i) ;
                    Serial.print(":(") ;
                         Serial.print(INPStr.substring(i,i+1)) ;
                    Serial.print(")\n") ;

              if (INPStr.substring(i,i+1) == "@")
                  {
                    Serial.print("find @ at :(") ;
                    Serial.print(i) ;
                         Serial.print("/") ;
                              Serial.print(strsize-i-1) ;
                         Serial.print("/") ;
                              Serial.print(INPStr.substring(i+1,strsize)) ;
                    Serial.print(")\n") ;
                      *r = byte(INPStr.substring(i+1,i+1+3).toInt()) ;
                      *g = byte(INPStr.substring(i+1+3,i+1+3+3).toInt() ) ;
                      *b = byte(INPStr.substring(i+1+3+3,i+1+3+3+3).toInt() ) ;
                       Serial.print("convert into :(") ;
                        Serial.print(*r) ;
                         Serial.print("/") ;
                        Serial.print(*g) ;
                         Serial.print("/") ;
                        Serial.print(*b) ;
                         Serial.print(")\n") ;
                            
                      return true ;
                  }
          }
    return false ;

}
void CheckLed()
{
     for(int i = 0 ; i <16; i++)
        {
              ChangeBulbColor(CheckColor[i][0],CheckColor[i][1],CheckColor[i][2]) ;
              delay(CheckColorDelayTime) ;
        }
}
void DebugMsg(String msg)
{
    if (_Debug != 0)
        {
          Serial.print(msg) ;
        }
   
}
void DebugMsgln(String msg)
{
    if (_Debug != 0)
        {
          Serial.println(msg) ;
        }
   
}

void initAll()
{

    Serial.begin(9600);
     Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("System Start") ; 
  //-------------------
    Serial.print("Ap Original Name :(");
    Serial.print(APid);
    Serial.print(")\n");
    MacData = GetMacAddress() ;
    ChangeAPName(APid) ;
    Serial.print("Ap name is changed:(");
    Serial.print(APid);
    Serial.print(")\n");
    while(true);

   //---------------------
    pixels.begin();
  pixels.setBrightness(255);  // Lower brightness and save eyeballs!
  pixels.show(); // Initialize all pixels to 'off'

 
    DebugMsgln("Program Start Here") ;
      pixels.begin(); // This initializes the NeoPixel library.
      DebugMsgln("init LED") ;
    ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
      DebugMsgln("Turn off LED") ;
      if (TestLed ==  1)
          {
               CheckLed() ;
                 DebugMsgln("Check LED") ;
                  ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
                  DebugMsgln("Turn off LED") ;
          }
 

      DebugMsgln("Clear Bluetooth Buffer") ;
    //  ClearBluetoothBuffer() ;

}

String GetMacAddress() {
  // the MAC address of your WiFi shield
  String Tmp = "" ;
  byte mac[6];
  
  // print your MAC address:
  WiFi.macAddress(mac);
  for (int i=0; i<6; i++)
    {
        Tmp.concat(print2HEX(mac[i])) ;
    }
    Tmp.toUpperCase() ;
  return Tmp ;
}



String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  return ttt ;
}



void ChangeAPName(char *pp)
{
  Serial.print("Inner Changeapname:(") ;
  Serial.print(pp) ;
  Serial.print("/") ;
  Serial.print(MacData) ;
  Serial.print(")\n") ;
//  MacData.toCharArray(Macchar,12) ;
  MacData.toCharArray(Macchar,12) ;
  memcpy(pp+6, &Macchar[6], 6)
  /*
   for(int i = 0; i<6;i++)
    {
      Serial.print("***") ;
      Serial.print(*(pp+4+i)) ;
      Serial.print("/") ;
      Serial.print(Macchar[6+i]) ;
      Serial.print("***\n") ;
       *(pp+4+i) = Macchar[6+i] ;
    }
    */
}
