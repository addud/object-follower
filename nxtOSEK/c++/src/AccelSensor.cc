//
// AccelSensor.cc
//
// Hi-Technic Acceleration / Tilt sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "AccelSensor.h"

//=============================================================================
// AccelSensor::AccelSensor(unsigned char _port)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//

AccelSensor::AccelSensor(unsigned char _port) {

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
// AccelSensor::~AccelSensor(void)
//   class destructor
//

AccelSensor::~AccelSensor(void) {

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
// void AccelSensor::activate(void)
//   turn on the sensor port
//

void AccelSensor::activate(void) {

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
// void AccelSensor::passivate(void)
//   turn off the port
//

void AccelSensor::passivate(void) {

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
// void AccelSensor::fetchData(short int axes[3])
//   fetch acceleration data from the sensor
//
// Parm
//   axes - array to hold acceleration data along the axes
//

void AccelSensor::fetchData(short int axes[3]) {
  int i;
  unsigned char inBuf[6];

  //
  // Data representation from the sensor, per Hi-Technic's documentation:
  //
  // data[0]: X axis upper 8 bits
  // data[1]: Y axis upper 8 bits
  // data[2]: Z axis upper 8 bits
  // data[3]: X axis lower 2 bits
  // data[4]: Y axis lower 2 bits
  // data[5]: Z axis lower 2 bits
  //

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x42,1,inBuf,6,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // convert raw data into final results
  //

  for (i=0; i<3; i++) {
    axes[i] = (S16)inBuf[i];
    if (axes[i] > 127) axes[i] -= 256;
    /* convert to 10 bit value */
    axes[i] = (axes[i] << 2) | ((S16)inBuf[i+3] & 0x0003);
  }
}



//=============================================================================
// short int AccelSensor::getXAccel(void)
//   get acceleration on X axis
//
// NB: positive is forward. 200 ticks per g.
//

short int AccelSensor::getXAccel(void) {
  short int axes[3];

  fetchData(axes);

  return axes[0];
}



//=============================================================================
// short int AccelSensor::getYAccel(void)
//   get acceleration on Y axis
//
// NB: positive is left. 200 ticks per g.
//

short int AccelSensor::getYAccel(void) {
  short int axes[3];

  fetchData(axes);

  return axes[1];
}



//=============================================================================
// short int AccelSensor::getZAccel(void)
//   get acceleration on Z axis
//
// NB: positive is up. 200 ticks per g.
//

short int AccelSensor::getZAccel(void) {
  short int axes[3];

  fetchData(axes);

  return axes[2];
}



//=============================================================================
// void AccelSensor::getAccel(short int axes[3])
//   get acceleration on all three axes
//

void AccelSensor::getAccel(short int axes[3]) {

  fetchData(axes);

}



//=============================================================================
// void AccelSensor::getAccel(short int &x,short int &y,short int &z) {
//  get acceleration on all three axes
//

void AccelSensor::getAccel(short int &x,short int &y,short int &z) {
  short int axes[3];

  fetchData(axes);

  x = axes[0];
  y = axes[1];
  z = axes[2];
}
