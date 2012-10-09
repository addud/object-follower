//
// SoundSensor.h
//
// Header for sound sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _SOUND_SENSOR_H
#define _SOUND_SENSOR_H

//
// these are necessary for data types associated with events and tasks, and the
// i2c function prototypes
//

extern "C" {
#include "kernel.h"
#include "nxt_avr.h"
  //#include "i2c.h"
#include "sensors.h"
};

//
// this has definitions for the C++ classes
//

#include "LejosOSEKCC.h"



//=============================================================================
// class SoundSensor
//   sound sensor class definition
//

class SoundSensor {
 public:
  SoundSensor(unsigned char _port,bool _dba=false);
  ~SoundSensor(void);

  void setDBA(bool _dba);

  inline bool isDBA(void) { return dba; }

  short int getValue(void);
  short int getRawValue(void);

 private:
  unsigned char port;
  bool dba;
};

#endif
