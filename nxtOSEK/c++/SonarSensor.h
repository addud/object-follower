//
// SonarSensor.h
//
// Header for sonar sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _SONAR_SENSOR_H
#define _SONAR_SENSOR_H

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
// class SonarSensor
//   sonar sensor class definition
//

class SonarSensor {
 public:
  SonarSensor(unsigned char _port);
  ~SonarSensor(void);

  void activate(void);
  void passivate(void);

  inline bool isActivated(void) { return activated; }

  short int getDistance(void);

 private:
  unsigned char port;
  bool activated;
};

#endif
