/* largeprogtest.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);

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

extern const U32 map[40000]; /* it consums 40000*4bytes = 160Kbytes in Flash */

/* Task1 executed every 10msec */
TASK(Task1)
{
	static int i = 0;

   	if (i >= 40000) i = 0;
	display_clear(0);
	display_goto_xy(0, 0);
   	display_int(map[i++], 0);
   	display_update();

	TerminateTask();
}
