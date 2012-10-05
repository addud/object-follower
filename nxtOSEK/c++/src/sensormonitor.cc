//
// cppTest.cc
//
// Test of C++ and LEJOS-OSEK
//
// Written 9-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//

extern "C" {

#include <LejosOSEKCC.h>
#include "ecrobot_interface.h"

  DeclareEvent(SensorEventMask);

TASK(SensorMonitorTask) {
  int i;
  
  for (i=0;i<N_SENSORS;i++)
    if (sensorWaiting[i] && i2c_busy(i) == 0) {
      SetEvent(sensorWaitID[i],SensorEventMask);
      sensorWaiting[i] = false;
    }
  
  TerminateTask();
}

};
