/* i2cwritetest.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
DeclareTask(Task2);

/* LEJOS OSEK hooks */
void ecrobot_device_terminate()
{
	i2c_disable(NXT_PORT_S2);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  StatusType ercd;

  ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
  if(ercd != E_OK)
  {
    ShutdownOS(ercd);
  }
}

/* Task1 executed only once at initialization */
TASK(Task1)
{
	nxt_avr_set_input_power(NXT_PORT_S2,2);
	i2c_enable(NXT_PORT_S2);

	TerminateTask();
}

/* Task2 executed every 500msec */
TASK(Task2)
{
	static U8 data;
	
	while (i2c_busy(NXT_PORT_S2) != 0);
	/* write Single shot command */
	data = 0x01;
	i2c_start_transaction(NXT_PORT_S2,1,0x41,1,&data,1,1);

	systick_wait_ms(50);

	if (i2c_busy(NXT_PORT_S2) == 0)
	{
		/* read mesurement data */	
		i2c_start_transaction(NXT_PORT_S2,1,0x42,1,&data,1,0);

		systick_wait_ms(50);

		display_clear(0);
		display_goto_xy(0, 0);
		display_int(data, 0);
		display_update();
	}

	TerminateTask();
}

