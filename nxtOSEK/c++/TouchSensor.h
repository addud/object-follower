//
// TouchSensor.h
//
// Header for touch sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _TOUCH_SENSOR_H
#define _TOUCH_SENSOR_H

//
// these are necessary for data types associated with events and tasks, and the
// i2c function prototypes
//

extern "C" {
#include "kernel.h"
#include "nxt_avr.h"
#include "i2c.h"
};

//
// this has definitions for the C++ classes
//

#include "LejosOSEKCC.h"



//=============================================================================
// class TouchSensor
//   compass sensor class definition
//

class TouchSensor {
 public:
  TouchSensor(unsigned char _port);
  ~TouchSensor(void);

  bool isPressed(void);

  short int getRawValue(void);

 private:
  unsigned char port;
};

#endif
