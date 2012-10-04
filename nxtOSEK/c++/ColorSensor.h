//
// ColorSensor.h
//
// Header for Hi-Technic color sensor class
//
// Written 12-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _COLOR_SENSOR_H
#define _COLOR_SENSOR_H

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
// class ColorSensor
//   color sensor class definition
//

class ColorSensor {
 public:
  ColorSensor(unsigned char _port);
  ~ColorSensor(void);

  void activate(void);
  void passivate(void);

  inline bool isActivated(void) { return activated; }

  unsigned char getColorNumber(void);
  unsigned char getColorIndex(void);

  void getColor(short int rgb[3]);
  void getColor(short int &r,short int &g,short int &b);
  short int getRed(void);
  short int getGreen(void);
  short int getBlue(void);

  void getRawColor(short int rgb[3]);
  void getRawColor(short int &r,short int &g,short int &b);
  short int getRawRed(void);
  short int getRawGreen(void);
  short int getRawBlue(void);

  void getNormalizedColor(short int rgb[3]);
  void getNormalizedColor(short int &r,short int &g,short int &b);
  short int getNormalizedRed(void);
  short int getNormalizedGreen(void);
  short int getNormalizedBlue(void);

 private:
  unsigned char port;
  bool activated;

  void fetchData(unsigned char buf[14]);
};

#endif
