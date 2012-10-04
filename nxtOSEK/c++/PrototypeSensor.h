//
// PrototypeSensor.h
//
// Header for HiTechnic prototype sensor class
//
// Written 23-feb-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _PROTOTYPE_SENSOR_H
#define _PROTOTYPE_SENSOR_H

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
// class PrototypeSensor
//   prototype sensor class definition
//

class PrototypeSensor {
 public:
  PrototypeSensor(unsigned char _port,unsigned int _sample=10);
  ~PrototypeSensor(void);

  void setSampleRate(unsigned int rate);
  void setDigitalPorts(unsigned char dir);
  void writeDigitalData(unsigned char data);
  unsigned char readDigitalData(void);
  void readAnalogData(unsigned int analogPorts[5]);
  unsigned int readAnalogData(int analogPort);

 private:
  unsigned char port;
  unsigned char digitalDir;
  unsigned int sampleRate;
};

#endif
