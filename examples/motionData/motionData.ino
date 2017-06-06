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
  int mot = (int)data.motion;
  if(mot == 129){
    int x = ADNS_3080.convTwosComp(data.dx);
    int y = ADNS_3080.convTwosComp(data.dy); 
    Serial.print("dx: ");
    Serial.print( x );
    Serial.print(" dy: ");
    Serial.println( y ); 
   }
}
