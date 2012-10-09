/* helloworld.c for TOPPERS/ATK(OSEK) */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	SINT vars[16] = {-100000, 0, 12345, 40, 1, -5, -300000, 40, 76, 50000000, 1, 2, 3, 4, 100, -1};
	while(1)
	{
  		ecrobot_sint_var_monitor(vars);
		systick_wait_ms(50); /* 50msec wait */
	}
}
