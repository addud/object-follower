/* sample.c for TOPPERS/ATK(OSEK) */

#include <string.h>

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

extern const U32 map[40000]; /* it consums 40000*4bytes = 160Kbytes in Flash */

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	display_clear(0);
	display_goto_xy(0, 0);

	/* Verify map values */
	int size = sizeof(map)/sizeof(U32);
	for(int i = 0; i < size; i++)
	{
		if ((i+1) != map[i])
		{
			display_string("NXT BIOS: ERROR");
			display_goto_xy(0, 1);
			display_int(i+1,0);
			display_goto_xy(0, 2);
			display_int(map[i],0);
			display_update();
			systick_wait_ms(10000);
			ecrobot_shutdown_NXT();
			break;
		}
	}

	display_string("NXT BIOS: OK");
	display_update();
	systick_wait_ms(2000);
	ecrobot_exec_NXT_BIOS();

	while(1); /* never reach here */
}
