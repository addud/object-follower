//
// sleep.cc
//
// LEJOS-OSEK Task sleep functions
//
// Written 9-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//

extern "C" {
#include "kernel.h"
#include <LejosOSEKCC.h>

DeclareEvent(SensorEventMask);
DeclareEvent(SleepEventMask);
};
bool sensorWaiting[N_SENSORS] = {0};
TaskType sensorWaitID[N_SENSORS];

TaskType sleeperID[N_SLEEPERS];
unsigned int sleepCounter[N_SLEEPERS];
bool isSleeping[N_SLEEPERS] = {0};

void sensorSleep(unsigned char port) {
  GetTaskID(sensorWaitID+port);
  sensorWaiting[port] = true;
  
  WaitEvent(SensorEventMask);
  ClearEvent(SensorEventMask);
}

void sleep(unsigned int duration) {
  
  for (int i=0;i<N_SLEEPERS;i++)
    if (!isSleeping[i]) {
      isSleeping[i] = true;
      sleepCounter[i] = duration;
      GetTaskID(sleeperID+i);
      WaitEvent(SleepEventMask);
      ClearEvent(SleepEventMask);
	  break;
    }
}
