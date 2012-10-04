//
// CompassSensor.cc
//
// Hi-Technic compass sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "CompassSensor.h"

//=============================================================================
// CompassSensor::CompassSensor(unsigned char _port)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//

CompassSensor::CompassSensor(unsigned char _port) {

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
// CompassSensor::~CompassSensor(void)
//   class destructor
//

CompassSensor::~CompassSensor(void) {

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
// void CompassSensor::activate(void)
//   turn on the sensor port
//

void CompassSensor::activate(void) {

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
// void CompassSensor::passivate(void)
//   turn off the port
//

void CompassSensor::passivate(void) {

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
// void CompassSensor::fetchData(unsigned char inBuf[5])
//   fetch raw compass data from the sensor
//
// Parm
//   inBuf - buffer to hold data
//

void CompassSensor::fetchData(unsigned char inBuf[5]) {

  //
  // Data representation from the sensor, per Hi-Technic's documentation:
  //
  // data[0]: mode control
  // data[1]: heading upper 8 bits
  // data[2]: heading lower 1 bit
  // data[3]: heading lower 8 bits
  // data[4]: heading upper 1 bit
  //

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x41,1,inBuf,5,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);
}



//=============================================================================
// short int getHeading(void)
//   return compass heading per Hi-Technic color chart
//

short int CompassSensor::getHeading(void) {
  unsigned char buf[5];

  fetchData(buf);

  return (short int)buf[3] | ((short int)buf[4] << 8);
}



//=============================================================================
// void beginCalibration(void)
//   start calibration mode
//

void CompassSensor::beginCalibration(void) {
  unsigned char cmd = 0x43;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x41,1,&cmd,1,1);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);
}



//=============================================================================
// bool endCalibration(void)
//   end calibration mode
//
// Returns true iff calibration was successful
//

bool CompassSensor::endCalibration(void) {
  unsigned char cmd = 0x0;

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x41,1,&cmd,1,1);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // now read back the byte, if it's 0 then calibration succeeded, otherwise
  // it'll be a 2 and it failed
  //

  i2c_start_transaction(port,1,0x41,1,&cmd,1,1);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  return !cmd;
}
