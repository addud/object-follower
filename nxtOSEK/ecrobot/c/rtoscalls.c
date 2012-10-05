/*
 * rtoscalls.c
 * 
 * This source file includes RTOS(ATK/JSP) dependent functions to be
 * invoked from ECRobot++ API. Currently, only ATK(OSEK) is supported.
 *
 * This source file is derived from sleep functions which is written
 * by Prof. Rovert W. Kramer
 *
 * Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
 */

#include "rtoscalls.h"

#include "ecrobot_base.h"


#ifdef NXT_JSP /* TOPPERS/JSP(uITRON) */
#else /* TOPPERS/ATK(OSEK) */
DeclareEvent(EventSleepI2C);
DeclareEvent(EventSleep);

static TaskType sleeperI2C_ID[MAX_N_SENSORS];
static TaskType sleeperTask_ID[N_TASKS];
static  U8 isI2cSleeping[MAX_N_SENSORS] = {0};
static  U8 isTaskSleeping[N_TASKS] = {0};
static U32 sleepTaskCounter[N_TASKS] = {0};
#endif


/* 
 * check sleeping I2C devices and Tasks
 * Note that this function must be executed from 1msec ISR hook
 */
void SleeperMonitor(void)
{
#ifdef NXT_JSP /* TOPPERS/JSP(uITRON) */

	/* ITRON provides dly_tsk API which is easy to sleep the task
	 * where the API was called, so SleeperMonitor is implemented as
	 * just an empty function.
	 *
	 * Special thanks to chihayafuru-san (http://www.chihayafuru.jp/)
	 */

#else /* TOPPERS/ATK(OSEK) */
	SINT i;

	/* check on sleeping I2C devices */
	for (i = 0; i<MAX_N_SENSORS; i++)
	{
		if (isI2cSleeping[i] && i2c_busy(i) == 0)
		{
			isI2cSleeping[i] = 0; /* reset a sleep flag */

			SetEvent(sleeperI2C_ID[i], EventSleepI2C); /* kick out the sleeping Task */
		}
	}

	/* check on sleeping Tasks */
	for (i = 0; i<N_TASKS; i++)
	{
		if (isTaskSleeping[i])
		{
			if (!--sleepTaskCounter[i])
			{
				isTaskSleeping[i] = 0; /* reset a sleep flag */

				SetEvent(sleeperTask_ID[i], EventSleep); /* kick out the sleeping Task */
			}
		}
	}
#endif
}

/* make a running Task sleep which has an I2C device until I2C becomes not busy */
void SleepI2C(U8 port)
{
#ifdef NXT_JSP /* TOPPERS/JSP(uITRON) */
	while (i2c_busy(port) == 1)
	{
		dly_tsk(0); /* wait for next tick */
	}

#else /* TOPPERS/ATK(OSEK) */
	if (i2c_busy(port) == 1)
	{
		TaskType id;

		GetTaskID(&id); /* get running Task ID */
		if (id != INVALID_TASK)
		{
			sleeperI2C_ID[port] = id; /* save the runninng Task ID */
			isI2cSleeping[port] = 1; /* set sleep flag */
			
			WaitEvent(EventSleepI2C); /* sleep until kicked up by the SleeperMonitor */
			ClearEvent(EventSleepI2C);
		}
	}
#endif
}

/* make a running Task sleep for duration time in msec */
void Sleep(U32 duration)
{
#ifdef NXT_JSP /* TOPPERS/JSP(uITRON) */
	dly_tsk((RELTIM) duration);

#else /* TOPPERS/ATK(OSEK) */
	for (SINT i = 0;i < N_TASKS; i++)
	{
		if (!isTaskSleeping[i])
		{
			TaskType id;

			GetTaskID(&id); /* get running Task ID */
			if (id != INVALID_TASK)
			{
				sleeperTask_ID[i] = id; /* save the runninng Task ID */
				isTaskSleeping[i] = 1; /* set sleep flag */
				sleepTaskCounter[i] = duration; /* set sleep time in msec */
				
				WaitEvent(EventSleep); /* sleep until kicked up by the SleeperMonitor */
				ClearEvent(EventSleep);
			}
			break;
		}
    }
#endif
}

void AssertDeviceConstructor(const CHAR* message)
{
#ifndef DISABLE_ECROBOT_DEVICE_ASSERT
	/*
	 * When an ECRobot C++ device object is
	 * constructed in local scope (not defined as a global object),
	 * this assertion displays an error message.
	 *
	 * The global constructors table executed prior to start OS
	 * in main function(ecrobot.c), so this get_OS_flag could be
	 * used to check the timing of device object constructions.
	 */
	if (get_OS_flag() == 1)
	{
		/* RTOS is already started, but a device object is constructed. */
		display_clear(0);
		display_goto_xy(0, 0);
		display_string(message);
		display_update();

		while(1);
	}
#endif
}

