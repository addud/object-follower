//
// CompassSensor.h
//
// Header for Hi-Technic compass sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _COMPASS_SENSOR_H
#define _COMPASS_SENSOR_H

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
// class CompassSensor
//   compass sensor class definition
//

class CompassSensor {
 public:
  CompassSensor(unsigned char _port);
  ~CompassSensor(void);

  void activate(void);
  void passivate(void);

  inline bool isActivated(void) { return activated; }

  short int getHeading(void);

  void beginCalibration(void);
  bool endCalibration(void);

 private:
  unsigned char port;
  bool activated;

  void fetchData(unsigned char buf[5]);
};

#endif
