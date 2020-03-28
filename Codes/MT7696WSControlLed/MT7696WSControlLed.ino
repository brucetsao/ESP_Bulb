#include "ws2812b.h"
#define DIGITALPINNUMBER  10
#define NUM_LEDS  16


ws2812b ledstrip = ws2812b(DIGITALPINNUMBER , NUM_LEDS);

void setup() {
  randomSeed(millis());

  Serial.begin(9600);
  Serial.println("ws2812b test");

}


void loop() {
      int r=0,g=0,b=0 ;
      ledstrip.begin();
      r = (int)random(0,255) ;
      g = (int)random(0,255) ;
      b = (int)random(0,255) ;
      
  for(int i = 0 ; i < NUM_LEDS ; i++)
    {
        ledstrip.setPixelColor(i,r,g,b);
    }
    ledstrip.show();
  delay(10000);
}
