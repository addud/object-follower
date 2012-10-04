/* sample.cpp for TOPPERS/JSP(ITRON) */ 

// ECRobot++ API
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


// nxtJSP hook to be invoked from an 1msec periodical ISR
void jsp_systick_low_priority(void)
{
	if (get_OS_flag()) /* check whether JSP already started or not */
	{
		isig_tim();          /* cyclic task dispatcher */
		check_NXT_buttons();
	}
}

// A JSP task
void tsk(VP_INT exinf)
{
	Lcd lcd;

	lcd.clear();
	lcd.putf("s", "Hello World");
	lcd.disp();

	while(1);
}
}
