//
// cppTest.cc
//
// Test of C++ and LEJOS-OSEK
//
// Written 9-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//

#include <CompassSensor.h>
#include <SonarSensor.h>

//
// To properly interface with LEJOS-OSEK, we need to use C linkage between our
// code and LEJOS-OSEK
//

extern "C" {

#include "ecrobot_interface.h"

  CompassSensor comp(NXT_PORT_S2);
  SonarSensor sonar(NXT_PORT_S1);

  //
  // Main task (thread) declarations
  //
  // You need one DeclareTask( ) per task/thread
  //

  DeclareTask(Task1);

  //
  // OSEK callback hooks. Often unused, but must exist for proper linkage
  //

  void StartupHook(void){
    
    comp.activate();
    sonar.activate();
  }

  void ShutdownHook(StatusType ercd){

    comp.passivate();
    sonar.passivate();
  }

  //
  // User tasks go here.
  //

  TASK(Task1) {

    display_clear(0);
    
    display_goto_xy(0,1);
    display_int(comp.getHeading(),0);
    
    display_goto_xy(0,3);
    display_int(sonar.getDistance(),0);

    display_update();

    sleep(1000);

    //
    // your task should end like this unless it's a one-shot task
    //

    TaskType t;
    GetTaskID(&t);
    ChainTask(t);
  }

};
