//
// avoid.cc
//
// Test of C++ and LEJOS-OSEK with TurtleBot II
//
// Written 20-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//

#include <Motor.h>
#include <SonarSensor.h>

//
// To properly interface with LEJOS-OSEK, we need to use C linkage between our
// code and LEJOS-OSEK
//

extern "C" {

  #include "ecrobot_interface.h"

  // Port configration for Sensor and Motor

  Motor leftMotor(NXT_PORT_A);
  Motor rightMotor(NXT_PORT_B);
  SonarSensor sonar(NXT_PORT_S1);

  //
  // Main task (thread) declarations
  //
  // You need one DeclareTask( ) per task/thread
  //

  DeclareTask(LeftMotorTask);
  DeclareTask(RightMotorTask);
  DeclareTask(SonarTask);

  //
  // LEJOS OSEK callback hooks
  //

  void ecrobot_device_initialize(void)
  {
    sonar.activate();
  }

  void ecrobot_device_terminate(void)
  {
    sonar.passivate();
  }

  //===========================================================================
  // User tasks go here.
  //

  enum { FORWARD,BACKWARD,LEFT_TURN,RIGHT_TURN,STOP };

  int robotAction = FORWARD;

  void showMessage(char* msg)
  {
  	display_clear(0);
  	display_goto_xy(0, 0);
  	display_string(msg);
  	display_update();
  }

  TASK(LeftMotorTask)
  {

    leftMotor.setPower(75);

    if (robotAction == FORWARD || robotAction == RIGHT_TURN)
    {
      leftMotor.forward();
    }
    else if (robotAction != STOP)
    {
      leftMotor.backward();
    }
    else
    {
      leftMotor.flt();
    }

    //
    // your task should end like this unless it's a one-shot task
    //

    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
  }

  TASK(RightMotorTask)
  {

    rightMotor.setPower(75);

    if (robotAction == FORWARD || robotAction == LEFT_TURN)
    {
      rightMotor.forward();
    }
    else if (robotAction != STOP)
    {
      rightMotor.backward();
    }
    else
    {
      rightMotor.flt();
    }

    //
    // your task should end like this unless it's a one-shot task
    //

    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
  }

  TASK(SonarTask)
  {
    int d = sonar.getDistance();

    if (d < 18)
    {
      robotAction = STOP;
      showMessage("STOP");

      sleep(250);

      robotAction = BACKWARD;
      showMessage("BACKWARD");
      
      sleep(500);

      robotAction = STOP;
      showMessage("STOP");

      sleep(250);

      robotAction = LEFT_TURN;
      showMessage("LEFT_TURN");

      sleep(750);

      robotAction = STOP;
      showMessage("STOP");

      sleep(250);

      d = sonar.getDistance();

      robotAction = RIGHT_TURN;
      showMessage("RIGHT_TURN");

      sleep(1500);

      robotAction = STOP;
      showMessage("STOP");

      sleep(250);

      if (d > sonar.getDistance())
      {
		robotAction = LEFT_TURN;
      	showMessage("LEFT_TURN");

		sleep(1500);

		robotAction = STOP;
	    showMessage("STOP");

		sleep(250);
      }
    }

    robotAction = FORWARD;
    showMessage("FORWARD");


    //
    // your task should end like this unless it's a one-shot task
    //

    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
  }
  	
}
