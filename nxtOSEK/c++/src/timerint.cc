//
// timerint.cc
//
// LEJOS-OSEK 1msec interrupt hook function for liblejososek.a library
//
// Written 9-jan-2008 by rwk
//
// Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
//

extern "C" {

#include <LejosOSEKCC.h>

  DeclareCounter(SensorMonitorCounter);
  DeclareEvent(SleepEventMask);

//
// timer interrupt handler. You shouldn't need to modify this.
//

void user_1ms_isr_type2(void) {
  StatusType ercd;
  
  //
  // increment sensor monitor counter
  //
  
  ercd = SignalCounter(SensorMonitorCounter);
  
  if(ercd != E_OK)
    ShutdownOS(ercd);
  
  //
  // check on sleeping processes
  //
  
  for (int i=0;i<N_SLEEPERS;i++)
    if (isSleeping[i])
      if (!--sleepCounter[i]) {
	int id = sleeperID[i];
	isSleeping[i] = false;
	SetEvent(id,SleepEventMask);
      }
}

};
