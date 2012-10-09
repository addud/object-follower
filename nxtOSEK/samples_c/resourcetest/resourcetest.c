/* resourcetest.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter( SysTimerCnt );
DeclareResource(resource1);
DeclareEvent(event1);
DeclareTask(LowTask);
DeclareTask(HighTask);

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	if(ercd != E_OK)
	{
		ShutdownOS(ercd);
	}
}

/* Definitions */
#define COUNT 5000000
int digits;
int lowtaskcount;
int hightaskcount;

TASK(LowTask)
{
    int rcount;

	ecrobot_debug1(digits, 1111, 0);
	for (rcount = 0; rcount < COUNT; rcount++); 
	ecrobot_debug1(digits, 1119, 0);

	GetResource(resource1);
	for(rcount = 0; rcount < COUNT; rcount++) digits++;
	SetEvent(HighTask, event1);
	ecrobot_debug1(digits, 1199, 0);
	for(rcount=0; rcount < COUNT; rcount++) digits--;
	ReleaseResource(resource1);

	ecrobot_debug1(digits, 1999, 0);

	TerminateTask();
}

TASK(HighTask)
{
	int rcount;

	ecrobot_debug2(digits, 2222, 1);
	for(rcount=0; rcount < COUNT; rcount++) digits++;
	ecrobot_debug2(digits, 2228, 1);
	for(rcount=0; rcount < COUNT; rcount++) digits++;

	WaitEvent(event1);
	ClearEvent(event1);
	ecrobot_debug2(digits, 2288, 1);
	for(rcount=0; rcount < COUNT; rcount++) digits++;

	GetResource(resource1);
 	ecrobot_debug2(digits, 2888, 1);
 	for (rcount = 0; rcount < COUNT; rcount++);
	ReleaseResource(resource1);

	ecrobot_debug2(digits,8888 , 1);

	TerminateTask();
}
