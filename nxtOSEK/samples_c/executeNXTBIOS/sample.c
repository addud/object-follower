/* sample.c for TOPPERS/ATK(OSEK) */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	int elapsed_time;
	int start_time = systick_get_ms();
	while(1)
	{
		elapsed_time = (systick_get_ms() - start_time)/1000; /* seconds */

		display_goto_xy(0, 0);
		display_string("NXT BIOS will be");
		display_goto_xy(0, 1);
		display_string("executed after");
		display_goto_xy(0, 2);
		display_string("10 seconds.");

		display_goto_xy(0, 4);
		display_string("Elapsed Time: ");
		display_int(elapsed_time, 0);

		display_goto_xy(0, 5);
		display_string("================");
		display_goto_xy(0, 7);
		display_string("      EXIT      ");
		display_update();

		if (elapsed_time >= 10)
		{
			ecrobot_exec_NXT_BIOS();
		}

		/* Turn off the NXT if gray rectangle button is pressed */
		if (ecrobot_get_button_state() & BTN_GRAY_RECT)
		{
			ecrobot_shutdown_NXT();
		}

		systick_wait_ms(100);
	}
}
