
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareCounter(SysTimerCnt);
DeclareResource(lcd);
DeclareTask(LowTask);
DeclareTask(HighTask);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/
int digits;

/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2(void)
{
	StatusType ercd;
	
	/*
	 *  Increment OSEK Alarm System Timer Count
     */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : LowTask                                                        */
/* Priority: 2                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: preemptive                                                     */
/*--------------------------------------------------------------------------*/
int lowtaskcount;
TASK(LowTask)
{
    int hcount, lcount;

    for (hcount = 0; hcount < 10; hcount++) {
		digits--;
		GetResource(lcd);

		ecrobot_debug1(digits, hcount, 0);
	    /* The following loop is to wait for the ISR triggered by ecrobot_debug
	     * (or the specific I/O statement inside ecrobot_debug) to complete
	     * This is a good example to show how explicit/implicit shared resource
	     * is needed to be protected against concurrent accesses from multiple Tasks
		 */
		for (lcount = 0; lcount < 3200; lcount++) ;

		ReleaseResource(lcd);
	}
	lowtaskcount++;

	TerminateTask();
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : HighTask                                                       */
/* Priority: 3                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: preemptive                                                     */
/*--------------------------------------------------------------------------*/
int hightaskcount;
TASK(HighTask)
{
	int hcount, lcount;

	for (hcount = 0; hcount < 10; hcount++) {
		digits++;
		GetResource(lcd);

		ecrobot_debug2(digits, hcount, 0);
	    /* The following loop is to wait for the ISR triggered by ecrobot_debug
	     * (or the specific I/O statement inside ecrobot_debug) to complete
	     * This is a good example to show how explicit/implicit shared resource
	     * is needed to be protected against concurrent accesses from multiple Tasks
		 */
        for (lcount = 0; lcount < 3200; lcount++) ;

		ReleaseResource(lcd);
	}
	hightaskcount++;

	TerminateTask();
}
