/* helloworld.c for TOPPERS/JSP */ 
#include "helloworld.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* NXT-JSP hook ISR to be invoked every 1msec */
void jsp_systick_low_priority(void)
{
	if (get_OS_flag()) /* check whether JSP already started or not */
	{
		check_NXT_buttons(); /* this must be called here to stop/exit the system */
	}
}

void tsk0(VP_INT exinf)
{
	while(1)
	{
		ecrobot_status_monitor("JSP HelloWorld!");
		systick_wait_ms(500); /* 500msec wait */
	}
}
