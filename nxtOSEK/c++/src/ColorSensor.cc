//
// ColorSensor.cc
//
// Hi-Technic color sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "ColorSensor.h"

//=============================================================================
// ColorSensor::ColorSensor(unsigned char _port)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//

ColorSensor::ColorSensor(unsigned char _port) {

  //
  // remember the port number for data transfers
  //

  port = _port;

  //
  // turn on the sensor port. This comes from Takashi's code
  //

  nxt_avr_set_input_power(port,POWER_ON);
  i2c_enable(port);

  //
  // we are now activated (avoids redundant calls later)
  //

  activated = true;
}



//=============================================================================
// ColorSensor::~ColorSensor(void)
//   class destructor
//

ColorSensor::~ColorSensor(void) {

  //
  // turn off power. Not sure if this is needed here.
  //

  nxt_avr_set_input_power(port,POWER_OFF);

  //
  // disable the port. This is necessary.
  //

  i2c_disable(port);
}



//=============================================================================
// void ColorSensor::activate(void)
//   turn on the sensor port
//

void ColorSensor::activate(void) {

  //
  // nothing to do if the port's already on
  //

  if (activated)
    return;

  //
  // turn on the port and power
  //

  nxt_avr_set_input_power(port,POWER_ON);
  i2c_enable(port);

  //
  // remember that we've done this
  //

  activated = true;
}



//=============================================================================
// void ColorSensor::passivate(void)
//   turn off the port
//

void ColorSensor::passivate(void) {

  //
  // nothing to do if the port's off
  //

  if (!activated)
    return;

  //
  // turn off the port. As with the destructor, I'm not sure if the first call
  // is needed.
  //

  nxt_avr_set_input_power(port,POWER_OFF);
  i2c_disable(port);

  //
  // remember what we did
  //

  activated = false;
}



//=============================================================================
// void ColorSensor::fetchData(unsigned char inBuf[14])
//   fetch raw color data from the sensor
//
// Parm
//   inBuf - buffer to hold data
//

void ColorSensor::fetchData(unsigned char inBuf[14]) {

  //
  // Data representation from the sensor, per Hi-Technic's documentation:
  //
  // data[0]: color number
  // data[1]: red saturation
  // data[2]: green saturation
  // data[3]: blue saturation
  // data[4]: raw red upper 2 bits
  // data[5]: raw red lower 8 bits
  // data[6]: raw green upper 2 bits
  // data[7]: raw green lower 8 bits
  // data[8]: raw blue upper 2 bits
  // data[9]: raw blue lower 8 bits
  // data[10]: color index (2 bits per r/g/b)
  // data[11]: normalized red
  // data[12]: normalized green
  // data[13]: normalized blue
  //

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x42,1,inBuf,14,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);
}



//=============================================================================
// unsigned char getColorNumber(void)
//   return color number per Hi-Technic color chart
//

unsigned char ColorSensor::getColorNumber(void) {
  unsigned char buf[14];

  fetchData(buf);

  return buf[0];
}



//=============================================================================
// unsigned char getColorIndex(void)
//   return 6-bit color index value, 2 bits for r/g/b
//

unsigned char ColorSensor::getColorIndex(void) {
  unsigned char buf[14];

  fetchData(buf);

  return buf[10] & 0x3f;
}



//=============================================================================
// void getColor(short int rgb[3])
//   get color saturation data
//
// Parm
//   rgb - array to hold color data
//

void ColorSensor::getColor(short int rgb[3]) {

  getColor(rgb[0],rgb[1],rgb[2]);
}



//=============================================================================
// void getColor(short int &r,short int &g,short int &b)
//   get color saturation data
//
// Parms
//   r,g,b - references to rgb vars
//

void ColorSensor::getColor(short int &r,short int &g,short int &b) {
  unsigned char buf[14];

  fetchData(buf);

  r = (short int)buf[1];
  g = (short int)buf[2];
  b = (short int)buf[3];
}



//=============================================================================
// short int getRed(void)
//   return red saturation level
//

short int ColorSensor::getRed(void) {
  short int r,g,b;

  getColor(r,g,b);
  
  return r;
}



//=============================================================================
// short int getGreen(void)
//   return green saturation level
//

short int ColorSensor::getGreen(void) {
  short int r,g,b;

  getColor(r,g,b);
  
  return g;
}



//=============================================================================
// short int getBlue(void)
//   return blue saturation level
//

short int ColorSensor::getBlue(void) {
  short int r,g,b;

  getColor(r,g,b);
  
  return b;
}



//=============================================================================
// void getRawColor(short int rgb[3])
//   get raw color saturation data
//
// Parm
//   rgb - array to hold color data
//

void ColorSensor::getRawColor(short int rgb[3]) {

  getRawColor(rgb[0],rgb[1],rgb[2]);
}



//=============================================================================
// void getRawColor(short int &r,short int &g,short int &b)
//   get raw color saturation data
//
// Parms
//   r,g,b - references to rgb vars
//

void ColorSensor::getRawColor(short int &r,short int &g,short int &b) {
  unsigned char buf[14];

  fetchData(buf);

  r = ((short int)buf[4] << 8) | ((short int)buf[5]);
  g = ((short int)buf[6] << 8) | ((short int)buf[7]);
  b = ((short int)buf[8] << 8) | ((short int)buf[9]);
}



//=============================================================================
// short int getRawRed(void)
//   return raw red saturation level
//

short int ColorSensor::getRawRed(void) {
  short int r,g,b;

  getRawColor(r,g,b);
  
  return r;
}



//=============================================================================
// short int getRawGreen(void)
//   return raw green saturation level
//

short int ColorSensor::getRawGreen(void) {
  short int r,g,b;

  getRawColor(r,g,b);
  
  return g;
}



//=============================================================================
// short int getRawBlue(void)
//   return raw blue saturation level
//

short int ColorSensor::getRawBlue(void) {
  short int r,g,b;

  getRawColor(r,g,b);
  
  return b;
}



//=============================================================================
// void getNormalizedColor(short int rgb[3])
//   get normalized color saturation data
//
// Parm
//   rgb - array to hold color data
//
// NB: highest value normalized to 255, other colors scaled accordingly
//

void ColorSensor::getNormalizedColor(short int rgb[3]) {

  getNormalizedColor(rgb[0],rgb[1],rgb[2]);
}



//=============================================================================
// void getNormalizedColor(short int &r,short int &g,short int &b)
//   get normalized color saturation data
//
// Parms
//   r,g,b - references to rgb vars
//

void ColorSensor::getNormalizedColor(short int &r,short int &g,short int &b) {
  unsigned char buf[14];

  fetchData(buf);

  r = (short int)buf[11];
  g = (short int)buf[12];
  b = (short int)buf[13];
}



//=============================================================================
// short int getNormalizedRed(void)
//   return normalized red saturation level
//

short int ColorSensor::getNormalizedRed(void) {
  short int r,g,b;

  getNormalizedColor(r,g,b);
  
  return r;
}



//=============================================================================
// short int getNormalizedGreen(void)
//   return normalized green saturation level
//

short int ColorSensor::getNormalizedGreen(void) {
  short int r,g,b;

  getNormalizedColor(r,g,b);
  
  return g;
}



//=============================================================================
// short int getNormalizedBlue(void)
//   return normalized blue saturation level
//

short int ColorSensor::getNormalizedBlue(void) {
  short int r,g,b;

  getNormalizedColor(r,g,b);
  
  return b;
}
