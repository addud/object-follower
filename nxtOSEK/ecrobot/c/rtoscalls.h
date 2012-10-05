#ifndef RTOSCALLS_H_
#define RTOSCALLS_H_

#include "kernel.h"
#include "ecrobot_interface.h"

/*
 * N_TASKS: max number of Tasks to be slept
 * Note that it needs to modify N_TASKS when Sleep APIs were used in more than 8 Tasks
 */
#define N_TASKS 8


#define MAX_N_SENSORS 4 /* I2C sensors can be used per a NXT is fixed as 4 (number of sensor ports) */


#ifdef NXT_JSP /* TOPPERS/JSP(uITRON) */
#else /* TOPPERS/ATK(OSEK) */
DeclareEvent(EventSleepI2C);
DeclareEvent(EventSleep);
#endif

extern void SleeperMonitor(void); /* SleeperMonitor must be invoked from 1msec periodical ISR hook */
/* Below functions must be used in Tasks */
extern void SleepI2C(U8 port);
extern void Sleep(U32 duration);
extern   U8 Tick(void);
extern  U32 Toc(void);

extern void AssertDeviceConstructor(const CHAR* message);

#endif
