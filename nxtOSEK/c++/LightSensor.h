//
// LightSensor.h
//
// Header for light sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _LIGHT_SENSOR_H
#define _LIGHT_SENSOR_H

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
// class LightSensor
//   light sensor class definition
//

class LightSensor {
 public:
  LightSensor(unsigned char _port,bool _lamp=true);
  ~LightSensor(void);

  void setLamp(bool _lamp);

  inline bool isLit(void) { return lamp; }

  short int getValue(void);
  short int getRawValue(void);

 private:
  unsigned char port;
  bool lamp;
};

#endif
