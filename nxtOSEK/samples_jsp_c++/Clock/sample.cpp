/* sample.cpp for TOPPERS/JSP(ITRON) */ 

// ECRobot++ API
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Lcd lcd;
Clock clock;

//*****************************************************************************
// FUNCTION		: jsp_systick_low_priority
// ARGUMENT		: none
// RETURN		: none
// DESCRIPTION 	: 1msec periodical ISR
//*****************************************************************************
void jsp_systick_low_priority(void)
{
	if (get_OS_flag()) /* check whether JSP already started or not */
	{
		isig_tim();          /* cyclic task dispatcher */
	}
}

void tsk_ini(VP_INT exinf)
{
	lcd.clear();
	lcd.putf("s", "Clock");
	
	clock.sleep(1); // wait for next tick
	
	clock.reset();
	
	act_tsk(TSK1);
	act_tsk(TSK2);
	act_tsk(TSK3);
}

void tsk1(VP_INT exinf)
{
	while(1)
	{
		lcd.cursor(0, 2);
		lcd.putf("sd", "Task1: ", clock.now(),8);
		lcd.disp();

		clock.sleep(999); // sleep over 999 msec
	}
}

void tsk2(VP_INT exinf)
{
	while(1)
	{
		lcd.cursor(0, 3);
		lcd.putf("sd", "Task2: ", clock.now(),8);

		clock.sleep(1999); // sleep over 1999 msec
	}
}

void tsk3(VP_INT exinf)
{
	while(1)
	{
		lcd.cursor(0, 4);
		lcd.putf("sd", "Task3: ", clock.now(),8);

		clock.sleep(2999); // sleep over 2999 msec
	}
}

void tsk_idl(VP_INT exinf)
{
	while(1)
	{
		check_NXT_buttons();
	}
}

}
