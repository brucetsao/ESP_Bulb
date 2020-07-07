// Faya-Nugget Sample Code 
// Date: 2015/1/27
// Module Name: RGB LED
// Module Number: #ngt-dp-rgb-1A
// Description: Quick RGB light up demonstraion

// Wiring: Module Pin ==> Arduino Pin
//                R ==> D2
//                G ==> D3
//                B ==> D4

// define pins
#define Rpin 9
#define Gpin 10
#define Bpin 11

int rx,gx,bx;
void setup()
{
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
}

void loop()
{
  for(rx=0 ;rx<=255;rx=rx+15)
  {analogWrite(Rpin,rx);
      for(gx=0;gx<=255;gx=gx+15)
      {analogWrite(Gpin,gx);
          for(bx=0;bx<=255;bx=bx+15)
          {analogWrite(Bpin,bx);
           delay(50);
          }
      }
  }
}



