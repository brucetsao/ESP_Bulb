#define LEDC_CHANNEL_0     0
#define LEDC1_CHANNEL_0    1
#define LEDC_TIMER_13_BIT  13
#define LEDC_BASE_FREQ     5000
#define LED_PIN            5
#define LED1_PIN           17

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
    uint32_t duty = (8191 / valueMax) * min(value, valueMax);
   ledcWrite(channel, duty);
}

void setup() {
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED_PIN, LEDC_CHANNEL_0);
  ledcSetup(LEDC1_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED1_PIN, LEDC1_CHANNEL_0);
}

void loop() {
  int brightness = 0;    
  for(brightness=0; brightness<255; brightness++)
  {
  ledcAnalogWrite(LEDC1_CHANNEL_0, brightness);
   delay(20); 
  }
  if ( brightness >= 255) {
    int brightness=255;
    for(brightness=255; brightness>0; brightness--)
    {
        ledcAnalogWrite(LEDC_CHANNEL_0, brightness);
        delay(20); 
    }
 Serial.println(brightness, DEC);
}
}
