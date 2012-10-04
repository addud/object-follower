#ifndef _SLEEP_H
#define _SLEEP_H

#include "kernel.h"
#include "ecrobot_interface.h"

#define N_SLEEPERS 1 /* this needs to be modified */

DeclareEvent(SleepEventMask);

extern void check_sleepers(void);
extern void sleep(unsigned int duration);

#endif
