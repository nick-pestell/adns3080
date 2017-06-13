#include <adns3080.h>

adns3080 ADNS_3080(8,10);

void setup() {
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  Serial.begin(115200);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();

}

void loop() {  
  burst_data data;
  ADNS_3080.burstRead(&data);
  //int x = ADNS_3080.convTwosComp(data.dx);
  //Serial.println(x);
  
  //int y = ADNS_3080.convTwosComp(data.dy);
  //Serial.println(y);
  
  int SQUAL = (int)data.squal;
  Serial.println( SQUAL ); 

  //int shutter = (int)data.shutter;
  //Serial.println(shutter);

  //int max_pix = (int)data.max_pix;
  //Serial.println(max_pix);
  
  delay(6); // need this delay to synchronise with serial read in matlab
}
