/* helloworld.c for TOPPERS/ATK(OSEK) */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	U8 buttons;
	int exit_count = 0;

	while(1)
	{
		buttons = ecrobot_get_button_state();

		display_clear(0);
		display_goto_xy(0, 0);
		if (buttons & BTN_RIGHT)
		{
			display_string("Right:ON");
		}
		else
		{
			display_string("Right:OFF");
		}

		display_goto_xy(0, 1);
		if (buttons & BTN_LEFT)
		{
			display_string("Left:ON");
		}
		else
		{
			display_string("Left:OFF");
		}

		display_goto_xy(0, 2);
		if (buttons & BTN_ORANGE_RECT)
		{
			display_string("Orange rect:ON");
		}
		else
		{
			display_string("Orange rect:OFF");
		}

		display_goto_xy(0, 3);
		if (buttons & BTN_GRAY_RECT)
		{
			display_string("Gray rect:ON");
			/* Keep pressing the gray rect button to exit the NXT */
			if (exit_count++ >= 10)
			{
				ecrobot_shutdown_NXT();
			}
		}
		else
		{
			display_string("Gray rect:OFF");
			exit_count = 0;
		}
		display_update();

		systick_wait_ms(100);
	}
}
