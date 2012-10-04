/* mathtest.c for TOPPERS/ATK(OSEK) */

#include <math.h>

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	double df;

	while(1)
	{
		display_clear(0);

		/* sin */
		df = sin(45);
		display_goto_xy(0, 0);
		display_string("sin(45) x 1e8 =");
		display_goto_xy(0, 1);
		display_int((int)(df*1e8), 0); /* 85090352 */

		/* sin */
		df = cos(45);
		display_goto_xy(0, 2);
		display_string("cos(45) x 1e8 =");
		display_goto_xy(0, 3);
		display_int((int)(df*1e8), 0); /* 52532198 */

		/* sqrt */
		df = sqrt(2);
		display_goto_xy(0, 4);
		display_string("sqrt(2) x 1e8 =");
		display_goto_xy(0, 5);
		display_int((int)(df*1e8), 0); /* 141421356 */

		display_update();

		systick_wait_ms(500); /* 500msec wait */
	}
}
