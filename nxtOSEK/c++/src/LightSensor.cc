//
// LightSensor.cc
//
// Light sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "LightSensor.h"

//=============================================================================
// LightSensor::LightSensor(unsigned char _port,bool _lamp)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//   _lamp - true iff built-in light is to be turned on
//

LightSensor::LightSensor(unsigned char _port,bool _lamp) {

  //
  // remember the port number for data transfers
  //

  port = _port;

  //
  // remember lamp state
  //

  lamp = _lamp;

  //
  // turn on lamp if so indicated
  //

  if (lamp)
    set_digi0(port);
  else
    unset_digi0(port);
}



//=============================================================================
// LightSensor::~LightSensor(void)
//   class destructor
//

LightSensor::~LightSensor(void) {

  //
  // turn off the light if it's on
  //

  if (lamp)
    unset_digi0(port);
}



//=============================================================================
// void setLamp(bool _lamp)
//   set the built-in lamp status
//

void LightSensor::setLamp(bool _lamp) {

  //
  // if new status == current status, there's nothing to do
  //

  if (lamp == _lamp)
    return;

  lamp = _lamp;

  if (lamp)
    set_digi0(port);
  else
    unset_digi0(port);
}



//=============================================================================
// short int getRawValue(void)
//   get raw light level
//
// NB: sensor_adc( ) returns high values for dark and low values for light;
//     this function reverses the range.
//

short int LightSensor::getRawValue(void) {

  return 1023 - sensor_adc(port);
}



//=============================================================================
// short int getValue(void)
//   get light level as percentage
//
// NB: sensor_adc( ) returns high values for dark and low values for light;
//     this function reverses the range.
//

short int LightSensor::getValue(void) {

  return ((1023 - sensor_adc(port))*100) >> 10;
}
