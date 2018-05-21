#include <adns3080.h>

adns3080 ADNS_3080(4,10);
byte frame_data[30][30];
byte SQUAL;
int mode;

void setup() {

  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  
  Serial.begin(115200);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();
}


void loop() {

  if (Serial.available() > 0){
    mode = (int)Serial.read();
    if (mode == 49){
      ADNS_3080.reset();
      ADNS_3080.writeTo(CONFIGURATION_BITS_REG,0x10);
      while (!Serial.available()){
        SQUAL  = ADNS_3080.readFrom(SQUAL_REG,1);
        Serial.write(SQUAL);
        }
      Serial.read();
    } else{
      ADNS_3080.captureFrame(frame_data);
      }
    }
}


