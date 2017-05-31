#include <adns3080.h>

adns3080 ADNS_3080(8,10);
byte frame_data[30][30];

void setup() {
  
  Serial.begin(9600);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();
}


void loop() {

  ADNS_3080.captureFrame(frame_data);
  
}