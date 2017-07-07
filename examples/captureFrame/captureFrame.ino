#include <adns3080.h>

adns3080 ADNS_3080(4,10);
byte frame_data[30][30];

void setup() {

  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  
  Serial.begin(115200);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();
}


void loop() {

  ADNS_3080.captureFrame(frame_data);
  
}
