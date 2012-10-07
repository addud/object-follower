/* sonartest.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/*
 * LEJOS NXJ development team fixed I2C issue on port S4.
 * This sample also verifies the updated I2C comm. functionality
 */
#define PORT_IN_USE NXT_PORT_S4

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
DeclareTask(Task2);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_sonar_sensor(PORT_IN_USE);
}
void ecrobot_device_terminate()
{
	ecrobot_term_sonar_sensor(PORT_IN_USE);
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
	int sonar;
	
	sonar = ecrobot_get_sonar_sensor(PORT_IN_USE);
	
 	TerminateTask();
}

TASK(Task2)
{
  ecrobot_status_monitor("Sonar Test");

  TerminateTask();
}
