/* AlarmManualTest.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

DeclareAlarm(Alarm1);
DeclareCounter(SysTimerCnt);

//*****************************************************************************
// FUNCTION		: user_1ms_isr_type2
// ARGUMENT		: none
// RETURN		: none
// DESCRIPTION 	: 1msec periodical OSEK type 2 ISR
//*****************************************************************************
void user_1ms_isr_type2(void)
{
	(void)SignalCounter(SysTimerCnt);
}

//*****************************************************************************
// TASK			: Task_Alarm
// ARGUMENT		: none
// RETURN		: none
// DESCRIPTION 	: Manually triggered an Alarm Task
//*****************************************************************************
TASK(Task_Alarm)
{
	static U16 count = 0;
	
	display_clear(0);
	display_goto_xy(0, 0);
	display_unsigned(count++, 0);
	display_update();	
	
	TerminateTask();
}

//*****************************************************************************
// TASK			: Task_Background
// ARGUMENT		: none
// RETURN		: none
// DESCRIPTION 	: Background(never terminated) Task
//*****************************************************************************
TASK(Task_Background)
{
	// Alarm1(Task_Alarm) is activated with 500msec period after 1000msec
	SetRelAlarm(Alarm1, 1000, 500);
	
	while(1);
}
