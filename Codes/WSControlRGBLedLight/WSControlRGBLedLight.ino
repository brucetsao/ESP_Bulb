#include <String.h>
#define Led_Red_Pin 8  //Red Light of RGB Led 
#define Led_Green_Pin 9   //Green Light of RGB Led 
#define Led_Blue_Pin 10   //Blue Light of RGB Led 
byte RedValue = 0, GreenValue = 0, BlueValue = 0;
String ReadStr = "      " ;
void setup() {
  // put your setup code here, to run once:
  pinMode(Led_Red_Pin, OUTPUT) ;
  pinMode(Led_Green_Pin, OUTPUT) ;
  pinMode(Led_Blue_Pin, OUTPUT) ;
  analogWrite(Led_Red_Pin,0) ;
  analogWrite(Led_Green_Pin,0) ;
  analogWrite(Led_Blue_Pin,0) ;
  
  Serial.begin(9600) ;
  Serial.println("Program Start Here") ;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() >0)
  {
    ReadStr = Serial.readStringUntil(0x23) ;
     //  Serial.read() ;
      Serial.print("ReadString is :(") ;
       Serial.print(ReadStr) ;
       Serial.print(")\n") ;
        if (DecodeString(ReadStr,&RedValue,&GreenValue,&BlueValue) )
           {
            Serial.println("Change RGB Led Color") ;
            analogWrite(Led_Red_Pin , RedValue)  ;
            analogWrite(Led_Green_Pin , GreenValue)  ;
            analogWrite(Led_Blue_Pin , BlueValue)  ;
           }
  }

  
}

boolean DecodeString(String INPStr, byte *r, byte *g , byte *b) 
{
                    Serial.print("check sgtring:(") ;
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
                              Se-ri-al.print(INPStr.substring(i+1,strsize)) ;
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

