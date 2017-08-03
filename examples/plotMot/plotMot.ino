#include <adns3080.h>

adns3080 ADNS_3080(4,10);

void setup() {
  Serial.begin(19200);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();

  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);

}

byte SQUAL;

void loop() {  
  //burst_data data;
  //ADNS_3080.burstRead(&data);
  //int x = ADNS_3080.convTwosComp(data.dx);
  //Serial.write(x);
  
  //int8_t y = data.dy;
 // Serial.write(y);
  
  //SQUAL = (int)data.squal;
  //Serial.write( data.squal );

  //int shutter = (int)data.shutter;
  //Serial.write(shutter);

  //int max_pix = (int)data.max_pix;
  //Serial.write(max_pix);
  
  //delay(50); // need this delay to synchronise with serial read in matlab

  SQUAL  = ADNS_3080.readFrom(SQUAL_REG,1);
  Serial.write(SQUAL); 
  
}
