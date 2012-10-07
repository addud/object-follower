//
// AccelSensor.h
//
// Header for Hi-Technic acceleration sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _ACCEL_SENSOR_H
#define _ACCEL_SENSOR_H

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
// class AccelSensor
//   acceleration sensor class definition
//

class AccelSensor {
 public:
  AccelSensor(unsigned char _port);
  ~AccelSensor();

  void activate(void);
  void passivate(void);

  short int getXAccel(void);
  short int getYAccel(void);
  short int getZAccel(void);

  void getAccel(short int axes[3]);
  void getAccel(short int &x,short int &y,short int &z);

  inline bool isActivated(void) { return activated; }

 private:
  unsigned char port;
  bool activated;

  void fetchData(short int axes[3]);
};

#endif
