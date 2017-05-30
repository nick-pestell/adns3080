#include <SPI.h>
#include <avr/pgmspace.h>

// define registers
#define PROD_ID_REG 0x00
#define REVISION_ID_REG 0x01
#define MOTION_REG 0x02
#define DELTA_X_REG 0x03
#define DELTA_Y_REG 0x04
#define SQUAL_REG 0x05
#define PIXEL_SUM 0x06
#define CONFIGURATION_BITS_REG 0x0a
#define EXTENDED_CONFIG_REG 0x0b
#define DATA_OUT_LOWER_REG 0x0c
#define DATA_OUT_UP_REG 0x0d
#define SHUTTER_LOWER_REG 0x0e
#define SHUTTER_UP_REG 0x0f
#define FRAME_PERIOD_LOWER_REG 0x10
#define FRAME_PERIOD_UP_REG 0x11
#define MOTION_CLEAR_REG 0x12
#define FRAME_CAPTURE_REG 0x13
#define SROM_ENABLE_REG 0x14
#define FRAME_PERIOD_MAXB_LOWER_REG 0x19
#define FRAME_PERIOD_MAXB_UP_REG 0x1a
#define FRAME_PERIOD_MINB_LOWER_REG 0x1b
#define FRAME_PERIOD_MINB_UP_REG 0x1c
#define SHUTTER_MAXB_LOWER_REG 0x1d
#define SHUTTER_MAXB_UP_REG 0x1e
#define SROM_ID_REG 0x1f
#define OBSERVATION_REG 0x3d
#define INVERSE_PRODUCT_ID_REG 0x3f
#define PIXEL_BURST_REG 0x40
#define MOTION_BURST_REG 0X50
#define SROM_LOAD_REG 0x60

// read/write address
#define WRITE 0x80
#define READ 0x00

// set slave select to pin 10
//const int slaveSelectPin = 10;
#define slaveSelectPin 10
#define resetPin 8

int x = 0;
int y = 0;

struct burst_data {
  byte motion;
  byte dx, dy;
  byte squal;
  byte shutter;
  byte max_pix;
  };

byte burst_frame[30][30]; 

int powerUp() {
  // reset ADNS 3080
  reset();

  // check connection
  digitalWrite(slaveSelectPin, LOW);
  int ID = (int) readFrom(PROD_ID_REG,1);
  delay(50);
  return ID;
}

void reset(){
  // reset ADNS 3080
  digitalWrite(resetPin, HIGH);
  delay(1);
  digitalWrite(resetPin, LOW);
  delay(35);  
  }

void setup() {
  Serial.begin(9600);
  
  // set slaveSelectPin as output 
  pinMode(slaveSelectPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  
  // initialise SPI with parameters  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  delay(10);

  
  // power up & test connection
  if(powerUp() == 23){
    Serial.println("connection succesful");

    // turn on sensitive mode
    writeTo(CONFIGURATION_BITS_REG,0X19);
    }
  else{
    Serial.println("connection unsuccesful");
    while(1){};
    }
  
  delay(10);

}

// send command to chip
void writeTo(byte reg, byte value){
  // make address with reg and write bit
  byte address = reg | WRITE;
  // select device
  digitalWrite(slaveSelectPin, LOW);

  SPI.transfer(address); // send address
  SPI.transfer(value); // send value
  delayMicroseconds(30);
  // de-select device
  digitalWrite(slaveSelectPin, HIGH);
  delayMicroseconds(30);
}

// recieve data from chip
byte readFrom(byte reg, int byteNo){
  // make address with reg and read bit
  byte address = reg & 0x7f;

  digitalWrite(slaveSelectPin, LOW);

  SPI.transfer(address); // send address
  delayMicroseconds(100);

  // recieve first byte
  byte result = SPI.transfer(0x00);
  
  // recieve remaining bytes and form single number
  byteNo--;
  if (byteNo > 0){
    result = result << 8; // shift to the left one byte
    delayMicroseconds(30);
    byte inByte = SPI.transfer(0x00); // recieve next byte
    result = result | inByte;
    byteNo--;     
  }
  // de-select
  delayMicroseconds(30);
  digitalWrite(slaveSelectPin, HIGH);
  delayMicroseconds(30);
  
  // return result
  return result;
}

void burstRead(struct burst_data *p){
    // make address with reg and read bit
  byte address =  MOTION_BURST_REG & 0x7f;

  // select device
  digitalWrite(slaveSelectPin,LOW);
  
  SPI.transfer(address);// send address
  delayMicroseconds(100);
  p->motion =  SPI.transfer(0x00);
  p->dx =  SPI.transfer(0x00);
  p->dy =  SPI.transfer(0x00);
  //p->squal =  SPI.transfer(0x00);
  //p->shutter =  SPI.transfer(0x00)<<8;
  //p->shutter |=  SPI.transfer(0x00);
  //p->max_pix =  SPI.transfer(0x00);
  
  digitalWrite(slaveSelectPin,HIGH);
  delayMicroseconds(5);
 
  }

// pointer to array in argument
void captureFrame(byte pdata[][30]){ 
  // write to frame capture register to prepare frame
  writeTo(FRAME_CAPTURE_REG,0x83);

  // make address with reg and read bit
  byte address =  PIXEL_BURST_REG & 0x7f;

  delayMicroseconds(10);

  // select device
  digitalWrite(slaveSelectPin,LOW);
  
  SPI.transfer(address);// send address
  delayMicroseconds(100);

  // read pixel data into array
  for (int i=0; i < 30; i++){
    for (int j=0; j <30; j++){
      pdata[i][j] = SPI.transfer(0x00)<<2; // remove 2 MSBs to get in normal grascale 
      // write to serial port for processing display frame.
      Serial.write(pdata[i][j]);
      delayMicroseconds(10);
      }}
    

  digitalWrite(slaveSelectPin,HIGH);
  delayMicroseconds(5);
}

int convTwosComp(byte b){
  int num = (int) b;
  if(b & 0x80){
    num = num - 256;
    }
  return num;
};

void loop() {
  //burst_data data;
  //burstRead(&data);

  //int mot = (int)data.motion;
  //if(mot == 129){
  //  int x = convTwosComp(data.dx);
  //  int y = convTwosComp(data.dy); 
  //  Serial.print("dx: ");
  //  Serial.print( x );
  //  Serial.print(" dy: ");
  //  Serial.println( y ); 
  // }

    captureFrame(burst_frame);
    Serial.write(10);
}

