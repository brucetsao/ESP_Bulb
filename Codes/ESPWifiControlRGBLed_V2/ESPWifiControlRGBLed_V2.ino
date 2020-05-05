
#include "Pinset.h"
#include <WiFi.h>
// WiFiClient client ;



// Set web server port number to 80
WiFiServer server(8080);
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?


// How many NeoPixels are attached to the Arduino?


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, WSPIN, NEO_GRB + NEO_KHZ800);




void setup() {
  // put your setup code here, to run once:
     initAll() ;
        Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(APid, APpwd);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("\n\nAP IP address: ");
  Serial.println(IP);
        server.begin();
  // client = server.available();       
    delay(initDelayTime) ;   //wait 2 seconds
     DebugMsgln("Waiting for Wifi APPs Connection") ;
}


void loop() 
{
  
 // WiFiClient client = server.available();
      Serial.println("Waiting for Connecting") ;  
   readok = false ;
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
  //------------------
 // if (server.available()>0)
 //   {
  WiFiClient client  = server.available() ;
      if (client)
      {
        Serial.println("Now Someone Access WebServer");
    
        Serial.println("new client");
        // an http request ends with a blank line
        //boolean currentLineIsBlank = true;
        while (client.connected())
          {
        //    Serial.print("client connected  in while");
       //       Serial.println(millis());
              if (client.available())
              {
                //  Serial.println("something readrable");
                c = client.read();
                Serial.print(c) ;
                // give the web browser time to receive the data
                if (c == '@')
                {
                          Serial.println("read head happen");
                      ReadStr = ""  ;
                      strtime =   millis() ;
                      count = 0 ;
                        while(true)     // for enter read string
                        {
                          
                          if (client.available())
                               {
                                    c = client.read();
                                     Serial.print(c) ;
    
                                      if (c == '#')
                                          {
                                            readok = true ;
                                            count ++ ;
                                            break ;                                     
                                          }   //  read ending  symbol
                                          else
                                          {
                                            ReadStr.concat(c) ;
                                     //       Serial.println(ReadStr) ;
                                            count ++ ;
                                          }
                               }    //end of client.available() 
                                    Serial.print("Time Consume:") ;
                                    Serial.println(millis() - strtime) ;
                                     if ((millis() - strtime ) > MaxReceiveWaitTime)
                                        {
                                                  Serial.println("waiting too long ");
                                            readok = false ;
                                            break ;
                                        }     //judge too long time to waiting
                                    if (count > MaxReceiveCharCount)
                                        {
                                                  Serial.println("Read Chars too many");
                                            readok = false ;
                                            break ;
                                        }   //judge read too more char
    
                        }   //end of read command string (FROM BEGIN @ AS WHILE)
    
    
                }   //(c == '@')  judge read starting symbol
                      
              }   //(client.available())  some data incoming
        
            // close the connection:
            if (readok)
                {
                  Serial.print("read string :");
                  Serial.println(ReadStr) ;
                    if (WifiDecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
                     {
                          DebugMsgln("Change RGB Led Color") ;
                          ChangeBulbColor(RedValue,GreenValue,BlueValue) ;
                     }    // end of if (WifiDecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
                  readok = false ;
                  ReadStr = "" ;
                }   // end of if (readok)
            Serial.println("Wait for Command");
        }   //end of while (client.connected())
        Serial.print("Client Disconnected");
       // free(client) ;
       // Serial.print("Client Status:(");
      //  Serial.print(client.status());
      //  Serial.print(")\n\n");
        
          //  return ;
          Serial.println("Waiting for Receiving") ;
      }   //  end of  if (client)

      
 //   } // end of   if (server.available()>0)

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
boolean WifiDecodeString(String INPStr, byte *r, byte *g , byte *b) 
{
                    Serial.print("check string:(") ;
                    Serial.print(INPStr) ;
                         Serial.print(")\n") ;

      int i = 0 ;
      int strsize = INPStr.length();

                      *r = byte(INPStr.substring(i,i+3).toInt()) ;
                      *g = byte(INPStr.substring(i+3,i+3+3).toInt() ) ;
                      *b = byte(INPStr.substring(i+3+3,i+3+3+3).toInt() ) ;
                       Serial.print("convert into :(") ;
                        Serial.print(*r) ;
                         Serial.print("/") ;
                        Serial.print(*g) ;
                         Serial.print("/") ;
                        Serial.print(*b) ;
                         Serial.print(")\n") ;
                       return true ;

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
    MacData = GetMacAddress() ;
    ChangeAPName() ;


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
 

      DebugMsgln("Clear Buffer") ;
   

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


void ChangeAPName()
{

  Serial.print("Inner Changeapname:(") ;
  Serial.print(NewAPname) ;
  Serial.print("/") ;
  NewAPname.concat(MacData.substring(6,12)) ;  
  Serial.print(NewAPname) ;
  Serial.print("/") ;
  strcpy(&APid[0],&NewAPname[0]) ;
  Serial.print(APid) ;
  Serial.print("\n") ;
 
}
