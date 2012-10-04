/*
 * sleep.c
 * 
 * C version of nxtOSEK Task sleep functions
 *
 * Originally written 9-jan-2008 by rwk
 *
 * Copyright 2007, 2008 by Takashi Chikamasa and Robert W. Kramer
 */

#include "kernel.h"
#include "ecrobot_interface.h"
#include "sleep.h"

DeclareEvent(SleepEventMask);

TaskType sleeperTaskID[N_SLEEPERS];
U32 sleepTaskCounter[N_SLEEPERS];
U8 isTaskSleeping[N_SLEEPERS] = {0};

void check_sleepers(void)
{   
	int i;
	int id;

	 /* check on sleeping Tasks */
	for (i = 0; i < N_SLEEPERS; i++)
	{
		if (isTaskSleeping[i])
		{
			if (!--sleepTaskCounter[i])
			{
				id = sleeperTaskID[i];
				isTaskSleeping[i] = 0;
				SetEvent(id,SleepEventMask);
			}
		}
	}
}

void sleep(unsigned int duration)
{
	int i;
	
	for (i = 0;i < N_SLEEPERS; i++)
	{
		if (!isTaskSleeping[i])
		{
			isTaskSleeping[i] = 1;
			sleepTaskCounter[i] = duration;
			GetTaskID(sleeperTaskID+i);
			WaitEvent(SleepEventMask);
			ClearEvent(SleepEventMask);
			break;
		}
    }
}
