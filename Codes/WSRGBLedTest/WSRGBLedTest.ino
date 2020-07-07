#include <String.h>
#include "Pinset.h"
#include <WiFi.h>
String connectstr ;
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, WSPIN, NEO_GRB + NEO_KHZ800);


byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "      " ;
int delayval = 500; // delay for half a second


void setup() {
  // put your setup code here, to run once:
     initAll() ;
}


void loop() {

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
