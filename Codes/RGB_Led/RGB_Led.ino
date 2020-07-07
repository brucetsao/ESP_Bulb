int LedRpin = 15;    // dual Led Color1 Pin
int LedGpin = 2;     // dual Led Color2 Pin
int LedBpin = 4;     // dual Led Color3 Pin
int i,j,k;

void setup() {
  pinMode(LedRpin, OUTPUT);
  pinMode(LedGpin, OUTPUT);
  pinMode(LedBpin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
for(i=0; i<1; i++)
  {
    for(j=0; j<1; j++)
      {
        for(k=0; k<1; k++)
          {
           digitalWrite(LedRpin, i);
           digitalWrite(LedGpin, j);
           digitalWrite(LedBpin, k);
          }
      }
      
  }

}
