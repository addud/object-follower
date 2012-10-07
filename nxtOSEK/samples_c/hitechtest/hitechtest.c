/* helloworld.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_accel_sensor(NXT_PORT_S3);
}
void ecrobot_device_terminate()
{
	ecrobot_term_accel_sensor(NXT_PORT_S3);
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

/* Task1 executed every 50msec */
TASK(Task1)
{
	U16 yaw_rate;
	S16 accel_data[3];
	
	yaw_rate   = ecrobot_get_gyro_sensor(NXT_PORT_S1);
	ecrobot_get_accel_sensor(NXT_PORT_S3, accel_data);

	display_clear(0);

	display_goto_xy(0, 0);
   	display_string("HiTech Test");

   	display_goto_xy(0, 1);
   	display_string("YAW:    ");
   	display_int(yaw_rate, 0);

   	display_goto_xy(0, 2);
   	display_string("X ACCEL:");
   	display_int(accel_data[0], 0);

   	display_goto_xy(0, 3);
   	display_string("Y ACCEL:");
   	display_int(accel_data[1], 0);

   	display_goto_xy(0, 4);
   	display_string("Z ACCEL:");
   	display_int(accel_data[2], 0);

   	display_update();

 	TerminateTask();
}
