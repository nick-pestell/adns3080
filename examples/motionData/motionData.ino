#include <adns3080.h>

adns3080 ADNS_3080(4,10);

void setup() {
  Serial.begin(115200);
  ADNS_3080.initSPI();
  ADNS_3080.powerUp();

  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
}

unsigned long Time = 0;
int squal;
byte mot;
int8_t x;
int8_t y;
void loop() {
  
  //burst_data data;
  //ADNS_3080.burstRead(&data);
  //check if movement
  //mot = data.motion;
  //if(mot & 0x80){
  //  x = (int8_t)data.dx;
  //  y = (int8_t)data.dy; 
  //  Serial.print("dx: ");
  //  Serial.println( x );
   // Serial.print(" dy: ");
   // Serial.println( y ); 
  // }
  squal  = ADNS_3080.readFrom(SQUAL_REG,1);
  Serial.write(squal);
  delay(50);
  

 
}
