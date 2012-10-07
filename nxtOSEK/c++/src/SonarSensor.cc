//
// SonarSensor.cc
//
// Sonar sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "SonarSensor.h"

//=============================================================================
// SonarSensor::SonarSensor(unsigned char _port)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//

SonarSensor::SonarSensor(unsigned char _port) {

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
// SonarSensor::~SonarSensor(void)
//   class destructor
//

SonarSensor::~SonarSensor(void) {

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
// void SonarSensor::activate(void)
//   turn on the sensor port
//

void SonarSensor::activate(void) {

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
// void SonarSensor::passivate(void)
//   turn off the port
//

void SonarSensor::passivate(void) {

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
// short int getDistance(void)
//   return distance in cm
//

short int SonarSensor::getDistance(void) {
  unsigned char buf;

  //
  // Data representation from the sensor
  //
  // data[0]: distance
  //

  //
  // wait a short amount of time to keep readings stable
  //

  sleep(75);

  //
  // wait for port to become available
  //

  if (i2c_busy(port))
    sensorSleep(port);

  //
  // initiate data transfer
  //

  i2c_start_transaction(port,1,0x42,1,&buf,1,0);

  //
  // wait for port to complete the transfer
  //

  if (i2c_busy(port))
    sensorSleep(port);

  return (short int)buf & 0xff;
}
