/* helloworld.c for TOPPERS/ATK(OSEK) */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	while(1)
	{
  		ecrobot_status_monitor("OSEK HelloWorld!");
		systick_wait_ms(500); /* 500msec wait */
	}
}
