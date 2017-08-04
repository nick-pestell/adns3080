#include <adns3080.h>

adns3080 ADNS_3080(4,10);

void setup() {
  Serial.begin(115200);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();

  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);

  ADNS_3080.writeTo(FRAME_PERIOD_MAXB_LOWER_REG,0x7E);
  ADNS_3080.writeTo(FRAME_PERIOD_MAXB_UP_REG,0xE);

}

byte upper;
byte lower;
uint16_t count;

void loop() {  

  upper = ADNS_3080.readFrom(FRAME_PERIOD_MAXB_UP_REG,1);
  lower = ADNS_3080.readFrom(FRAME_PERIOD_MAXB_LOWER_REG,1); 
  count = (upper <<8 )|lower;
  
  Serial.println(count);
  
}
