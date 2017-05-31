/*
  adns3080.h 
*/
#ifndef adns3080_h
#define adns3080_h

#include "Arduino.h"
#include <SPI.h>

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

struct burst_data {
	byte motion;
	byte dx, dy;
	byte squal;
	byte shutter;
	byte max_pix;
	};

class adns3080
{
  public:
    adns3080(int resetPin, int slaveSelectPin);
    int powerUp();
    void reset();
    void writeTo(byte reg, byte value);
    byte readFrom(byte reg, int byteNo);
    void burstRead(struct burst_data *p);
    void captureFrame(byte pdata[][30]);
    int convTwosComp(byte b);
	void initSPI();
	
  private:
	int _resetPin;
	int _slaveSelectPin;

};

#endif