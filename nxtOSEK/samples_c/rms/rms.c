/* rms.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(TaskLCD);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
  nxt_motor_set_speed(NXT_PORT_A, 0, 1); 
  nxt_motor_set_speed(NXT_PORT_B, 0, 1); 
}

void ecrobot_device_terminate()
{
  nxt_motor_set_speed(NXT_PORT_A, 0, 1); 
  nxt_motor_set_speed(NXT_PORT_B, 0, 1); 
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

/* Task1 executed every 1msec */
TASK(Task1)
{
  if (ecrobot_get_touch_sensor(NXT_PORT_S1))
  {
    nxt_motor_set_speed(NXT_PORT_A, 0, 1);
  }
  else
  { 
    nxt_motor_set_speed(NXT_PORT_A, 50, 1);
  }

  TerminateTask();
}

/* Task2 executed every 500msec */
TASK(Task2)
{
  if (ecrobot_get_touch_sensor(NXT_PORT_S1))
  {
    nxt_motor_set_speed(NXT_PORT_B, 0, 1);
  }
  else
  { 
    nxt_motor_set_speed(NXT_PORT_B, 50, 1);
  }

  TerminateTask();
}

/* TaskLCD executed every 500msec */
TASK(TaskLCD)
{
  ecrobot_status_monitor("RMS");

  TerminateTask();
}

