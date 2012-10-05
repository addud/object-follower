/* rcxtest.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_set_RCX_power_source(NXT_PORT_S1);
	ecrobot_set_RCX_power_source(NXT_PORT_S4);
}
void ecrobot_device_terminate()
{
	ecrobot_term_RCX_power_source(NXT_PORT_S1);
	ecrobot_term_RCX_power_source(NXT_PORT_S4);
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

/* Task1 executed every 500msec */
TASK(Task1)
{
  S16 light_sensor;
  S16 rev_sensor;
  U8  touch_sensor;
	
  light_sensor = ecrobot_get_RCX_sensor(NXT_PORT_S1);
  touch_sensor = ecrobot_get_RCX_touch_sensor(NXT_PORT_S2);
  rev_sensor   = ecrobot_get_RCX_sensor(NXT_PORT_S4);
	
  display_clear(0);

  display_goto_xy(0, 0);
  display_string("RCX Test");

  display_goto_xy(0, 2);
  display_string("Light: ");
  display_int(light_sensor, 0);

  display_goto_xy(0, 3);
  display_string("Touch: ");
  display_int(touch_sensor, 0);

  display_goto_xy(0, 4);
  display_string("  Rev: ");
  display_int(rev_sensor, 0);

  display_update();

  TerminateTask();
}
