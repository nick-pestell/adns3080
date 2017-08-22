/*
	adns3080.cpp
*/

#include "Arduino.h"
#include "adns3080.h"
#include <SPI.h>

/*struct burst_data {
  byte motion;
  byte dx, dy;
  byte squal;
  byte shutter;
  byte max_pix;
  }; */
  
adns3080::adns3080(int resetPin, int slaveSelectPin){
	
	
	// set up chip select and reset pins
	pinMode(resetPin, OUTPUT);
	pinMode(slaveSelectPin, OUTPUT);

	_resetPin = resetPin;
	_slaveSelectPin = slaveSelectPin;
	
}

void adns3080::initSPI(){
	
	// initialize SPI with parameters
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE3);
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	delay(10);
}

// power up routine
int adns3080::powerUp(){
	// reset ADNS 3080
	reset();
	
	//check connection
	digitalWrite(_slaveSelectPin, LOW);
	int ID = (int)readFrom(PROD_ID_REG,1);
	delay(50);
	
	// test connection
	if(ID == 23){
		//Serial.println("connection succesful");
		// turn on sensitive mode
		writeTo(CONFIGURATION_BITS_REG,0x10);
		}
	else{
		//Serial.println("connection unsuccesful");
		}
	
	delay(10);
	return ID;
	
	}

// reset routine
void adns3080::reset(){
	// reset ADNS 3080
	digitalWrite(_resetPin, HIGH);
	delay(1);
	digitalWrite(_resetPin, LOW);
	delay(35);
	}
	
// send command to adns3080
void adns3080::writeTo(byte reg, byte value){

  // make address with reg and write bit
  byte address = reg | WRITE;
  // select device
  digitalWrite(_slaveSelectPin, LOW);

  SPI.transfer(address); // send address
  SPI.transfer(value); // send value
  delayMicroseconds(30);
  // de-select device
  digitalWrite(_slaveSelectPin, HIGH);
  delayMicroseconds(30);
}

// recieve data from adns3080
byte adns3080::readFrom(byte reg, int byteNo){

  // make address with reg and read bit
  byte address = reg & 0x7f;

  digitalWrite(_slaveSelectPin, LOW);

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
  digitalWrite(_slaveSelectPin, HIGH);
  delayMicroseconds(30);
  
  // return result
  return result;
}

// burst read motion data from adns3080
void adns3080::burstRead(struct burst_data *p){
  
  //Serial.println("in burst read");
  
  // make address with reg and read bit
  byte address =  MOTION_BURST_REG & 0x7f;

  // select device
  digitalWrite(_slaveSelectPin,LOW);
  
  SPI.transfer(address);// send address
  delayMicroseconds(100);
  p->motion =  SPI.transfer(0x00);
  p->dx =  SPI.transfer(0x00);
  p->dy =  SPI.transfer(0x00);
  p->squal =  SPI.transfer(0x00);
  //p->shutter =  SPI.transfer(0x00)<<8;
  //p->shutter |=  SPI.transfer(0x00);
  //p->max_pix =  SPI.transfer(0x00);
  

  
  digitalWrite(_slaveSelectPin,HIGH);
  delayMicroseconds(5);
 
  }
  
// capture an image
void adns3080::captureFrame(byte pdata[][30]){ 

  // write to frame capture register to prepare frame
  writeTo(FRAME_CAPTURE_REG,0x83);

  // make address with reg and read bit
  byte address =  PIXEL_BURST_REG & 0x7f;

  delay(5);

  // select device
  digitalWrite(_slaveSelectPin,LOW);
  
  SPI.transfer(address);// send address
  delay(1);

  // read pixel data into array
  for (int i=0; i < 30; i++){
    for (int j=0; j <30; j++){
      pdata[i][j] = SPI.transfer(0x00); 
      // write to serial port for processing display frame
      Serial.write(pdata[i][j]);
      }}
    

  digitalWrite(_slaveSelectPin,HIGH);
  // signal end of frame 
  //Serial.println();
  Serial.write(10);
  
}

// twos compliment --> integer
int adns3080::convTwosComp(byte b){

  int num = (int) b;
  if(b & 0x80){
    num = num - 256;
    }
  return num;
}
