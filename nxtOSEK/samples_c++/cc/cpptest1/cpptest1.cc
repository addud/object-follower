//
// cpptest1.cc
//
// Sample for C++ and LEJOS-OSEK
//
// Written 20-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//

#include <Motor.h>
#include <TouchSensor.h>

//
// To properly interface with LEJOS-OSEK, we need to use C linkage between our
// code and LEJOS-OSEK
//

extern "C" {

  #include "ecrobot_interface.h"

  // Port configration for Sensor and Motor
  
  Motor motor(NXT_PORT_C);
  TouchSensor touch(NXT_PORT_S4);

  //
  // Main task (thread) declarations
  //
  // You need one DeclareTask( ) per task/thread
  //

  DeclareTask(MotorTask);
  DeclareTask(TouchTask);

  //
  // User tasks go here.
  //

  enum { FORWARD,STOP };

  int robotAction = STOP;

  TASK(MotorTask)
  {

    if (robotAction == FORWARD)
    {
      motor.setPower(75);
      motor.forward();
    }
    else if (robotAction == STOP)
    {
      motor.stop();
    }

    //
    // your task should end like this unless it's a one-shot task
    //

    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
  }

  TASK(TouchTask)
  {

    if (touch.isPressed())
    {
    	robotAction = FORWARD;
    }
    else
    {
    	robotAction = STOP;
    }

    //
    // your task should end like this unless it's a one-shot task
    //

    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
  }
  	
}
