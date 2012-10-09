//
// Motor.cc
//
// Motor class
//
// Written 20-jan-2008 by rwk
//
// Copyright 2007, 2008 by Robert W. Kramer and Takashi Chikamasa
//
// Notes
//
// This is a rather rudimentary class. There is no attempt at speed regulation
// or smooth acceleration. That's for someone else, or for me to try at a
// later date.
//

#include "Motor.h"

//=============================================================================
// Motor::Motor(unsigned char _port)
//   constructor
//

Motor::Motor(unsigned char _port) {

  port = _port;
  powerPercent = 0;
}



//=============================================================================
// Motor::~Motor(void)
//   destructor
//
// Shuts off the motor with braking. Change third parameter to 0 to float
//

Motor::~Motor(void) {

  nxt_motor_set_speed(port,0,1);
}



//=============================================================================
// void Motor::forward(void)
//   starts motor moving forward
//

void Motor::forward(void) {

  nxt_motor_set_speed(port,powerPercent,0);
  isForward = true;
}



//=============================================================================
// void Motor::backward(void)
//   starts motor moving backward
//

void Motor::backward(void) {

  nxt_motor_set_speed(port,-powerPercent,0);
  isForward = false;
}



//=============================================================================
// void Motor::reverseDirection(void)
//   switches motor direction
//

void Motor::reverseDirection(void) {

  isForward = !isForward;

  nxt_motor_set_speed(port,isForward?powerPercent:-powerPercent,0);
}




//=============================================================================
// void Motor::stop(void)
//   stops the motor with braking
//

void Motor::stop(void) {

  nxt_motor_set_speed(port,0,1);
}



//=============================================================================
// void Motor::flt(void)
//   stops the motor with floating
//

void Motor::flt(void) {

  nxt_motor_set_speed(port,0,0);
}



//=============================================================================
// int Motor::getTachoCount(void)
//   return rotation count
//
// Note: this is untested, but it should work, since it's what LEJOS uses
//

int Motor::getTachoCount(void) {

  return nxt_motor_get_count(port);
}



//=============================================================================
// void Motor::resetTachoCount(void)
//   reset rotation counter to zero
//

void Motor::resetTachoCount(void) {

  nxt_motor_set_count(port,0);
}



//=============================================================================
// void Motor::setPower(int _power)
//   set motor power
//
// Range: -100 to 100, representing percent
//

void Motor::setPower(int _power) {

  powerPercent = _power;
}

  /*

  These are for later implementation, to complete a LEJOS-equivalent API

//  void rotate(int angle,bool immRet=false);

//  void setRegulated(bool _regulate);

//  void setSpeed(int _speed);

//  void setSmoothAcceleration(bool _smooth);

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
