//
// SoundSensor.cc
//
// Sound sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#include "SoundSensor.h"

//=============================================================================
// SoundSensor::SoundSensor(unsigned char _port,bool _lamp)
//   constructor for sensor object
//
// Parm
//   _port - port number sensor is connected to
//   _lamp - true iff set to DBA mode
//

SoundSensor::SoundSensor(unsigned char _port,bool _dba) {

  //
  // remember the port number for data transfers
  //

  port = _port;

  //
  // remember dba state
  //

  dba = _dba;

  //
  // turn on dba mode if so indicated
  //

  if (dba) {
    set_digi1(port);
    unset_digi0(port);
  } else {
    unset_digi1(port);
    set_digi0(port);
  }
}



//=============================================================================
// SoundSensor::~SoundSensor(void)
//   class destructor
//

SoundSensor::~SoundSensor(void) {

  unset_digi0(port);
  unset_digi1(port);
}



//=============================================================================
// void setDBA(bool _dba)
//   set the DBA status
//

void SoundSensor::setDBA(bool _dba) {

  //
  // if new status == current status, there's nothing to do
  //

  if (dba == _dba)
    return;

  dba = _dba;

  if (dba) {
    set_digi1(port);
    unset_digi0(port);
  } else {
    unset_digi1(port);
    set_digi0(port);
  }
}



//=============================================================================
// short int getValue(void)
//   get sound level as percent
//

short int SoundSensor::getValue(void) {

  return ((1023 - sensor_adc(port)) * 100) >> 10;
}



//=============================================================================
// short int getRawValue(void)
//   get raw sound level
//

short int SoundSensor::getRawValue(void) {

  return 1023 - sensor_adc(port);
}
