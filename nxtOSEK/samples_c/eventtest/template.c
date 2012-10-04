
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/*--------------------------------------------------------------------------*/
/* OSEK declarations                                                        */
/*--------------------------------------------------------------------------*/
DeclareEvent(BarrierEvent);
DeclareTask(LowTask);
DeclareTask(HighTask);

/*--------------------------------------------------------------------------*/
/* Definitions                                                              */
/*--------------------------------------------------------------------------*/
int digits;

/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2(){}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : LowTask                                                        */
/* Priority: 2                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: preemptive                                                     */
/*--------------------------------------------------------------------------*/
TASK(LowTask)
{
    int hcount, lcount;

    while(1) {
	  for (hcount = 0; hcount < 10; hcount++) {
		  for (lcount = 0; lcount < 3200; lcount++) ;
		  digits--;
 		  ecrobot_debug1(digits, hcount, 0);
	  }
      SetEvent(HighTask, BarrierEvent);
    }

    TerminateTask(); /* or ChainTask() */
}

/*--------------------------------------------------------------------------*/
/* Task information:                                                        */
/* -----------------                                                        */
/* Name    : HighTask                                                       */
/* Priority: 3                                                              */
/* Typ     : EXTENDED TASK                                                  */
/* Schedule: preemptive                                                     */
/*--------------------------------------------------------------------------*/
TASK(HighTask)
{
	int hcount, lcount;

	while(1) {
		for (hcount = 0; hcount < 10; hcount++) {
			for (lcount = 0; lcount < 3200; lcount++) ;
			  digits++;
	 		  ecrobot_debug2(digits, hcount, 0);
	  	}
   		WaitEvent(BarrierEvent);
        ClearEvent(BarrierEvent);
        digits=0;
    }

    TerminateTask(); /* or ChainTask() */
}

