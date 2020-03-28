#define _Debug 1
#define TestLed 1
#include <String.h>
#define WSPIN            15
#define NUMPIXELS      16
#define RXD2 16
#define TXD2 17
long strtime ;
String connectstr ;
String MacData ;
// Replace with your network credentials
char* APid = "BLUB1234" ;
//char APid[8] ;
char* APpwd = "12345678";
byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "      " ;
int delayval = 500; // delay for half a second
boolean readok = false ;
char c ;
int count ;
#define CheckColorDelayTime 200
#define initDelayTime 2000
#define CommandDelay 100

#define MaxReceiveWaitTime 3000
#define MaxReceiveCharCount 30
#define CheckColorDelayTime 500
#define initDelayTime 2000
#define CommandDelay 100

int CheckColor[][3] = {
                          {255 , 255,255} ,
                          {255 , 0,0} ,
                          {0 , 255,0} ,
                          {0 , 0,255} ,
                          {255 , 128,64} ,
                          {255 , 255,0} ,
                          {0 , 255,255} ,
                          {255 , 0,255} ,
                          {255 , 255,255} ,
                          {255 , 128,0} ,
                          {255 , 128,128} ,
                          {128 , 255,255} ,
                          {128 , 128,192} ,
                          {0 , 128,255} ,
                          {255 , 0,128} ,
                          {128 , 64,64} ,
                          {0 , 0,0} } ;
                     
                          
