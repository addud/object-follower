//
// TouchSensor.cc
//
// Touch sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "TouchSensor.h"

//=============================================================================
// TouchSensor::TouchSensor(unsigned char _port)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//

TouchSensor::TouchSensor(unsigned char _port) {

  //
  // remember the port number for data transfers
  //

  port = _port;
}



//=============================================================================
// TouchSensor::~TouchSensor(void)
//   class destructor
//

TouchSensor::~TouchSensor(void) { }



//=============================================================================
// bool isPressed(void)
//   return true iff sensor is pressed
//

bool TouchSensor::isPressed(void) {

  return (sensor_adc(port) < 512);
}



//=============================================================================
// short int getRawValue(void)
//   get unmodified value
//

short int TouchSensor::getRawValue(void) {

  return sensor_adc(port);
}
