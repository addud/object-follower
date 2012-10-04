/* datalogging.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_sonar_sensor(NXT_PORT_S2);
	ecrobot_init_bt_slave("LEJOS-OSEK");
}

void ecrobot_device_terminate()
{
	ecrobot_term_sonar_sensor(NXT_PORT_S2);
	ecrobot_term_bt_connection();
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
	if (ercd != E_OK)
	{
		ShutdownOS(ercd);
	}
}

/* Task1 executed every 50msec */
TASK(Task1)
{
	static S8 i,j;
	int sonar;

	sonar = ecrobot_get_sonar_sensor(NXT_PORT_S2);

	/* send Sensor/Motors/NXT internal status to the host.
	 * NXT GamePad in the host PC accumulates all logging data
	 * and later you can save the logging data into a CSV file
	 */
	ecrobot_bt_data_logger(i++, j--);

	/* display Sensors/Motors/NXT internal status */ 
	ecrobot_status_monitor("Data Logging");

	TerminateTask();
}
