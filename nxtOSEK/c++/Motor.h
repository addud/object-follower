//
// Motor.h
//
// Header for motor class
//
// Written 13-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//

#ifndef _MOTOR_H
#define _MOTOR_H

//
// these are necessary for data types associated with events and tasks, and the
// i2c function prototypes
//

extern "C" {
  #include "kernel.h"
  #include "nxt_motors.h"
};

//
// this has definitions for the C++ classes
//

#include "LejosOSEKCC.h"



//=============================================================================
// class Motor
//   motor class definition
//

class Motor {
 public:
  Motor(unsigned char _port);
  ~Motor(void);

  void forward(void);
  void backward(void);
  void reverseDirection(void);

  void stop(void);
  void flt(void);

  int getTachoCount(void);
  void resetTachoCount(void);

  void setPower(int _power);

  /*

  These methods are for later development... the goal is to create the same
  API as in LEJOS.

  //  void setSmoothAcceleration(bool _smooth);

  //  void rotate(int angle,bool immRet=false);

  //  void setRegulated(bool _regulate);

  //  void setSpeed(int _speed);
  int getActualSpeed(void);
  int getLimitAngle(void);
  int getMode(void);
  int getPower(void);
  int getSpeed(void);
  int getStopAngle(void);
  bool isMoving(void);
  bool isRegulating(void);
  bool isRotating(void);
  void rotateTo(int angle,bool immRet=false);
  
  */

 private:
  unsigned char port;
  bool activated,isForward;
  int powerPercent;

};

#endif
