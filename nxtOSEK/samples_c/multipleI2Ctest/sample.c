/* sample.c */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
DeclareTask(Task2);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_accel_sensor(NXT_PORT_S1);
	ecrobot_init_accel_sensor(NXT_PORT_S2);
	ecrobot_init_sonar_sensor(NXT_PORT_S3);
	ecrobot_init_sonar_sensor(NXT_PORT_S4);
}
void ecrobot_device_terminate()
{
	ecrobot_term_accel_sensor(NXT_PORT_S1);
	ecrobot_term_accel_sensor(NXT_PORT_S2);
	ecrobot_term_sonar_sensor(NXT_PORT_S3);
	ecrobot_term_sonar_sensor(NXT_PORT_S4);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
  (void)SignalCounter(SysTimerCnt);
}

S16 accel[2][3];
S32 sonarS3, sonarS4;

/* Task1 executed every 50msec */
TASK(Task1)
{
	ecrobot_get_accel_sensor(NXT_PORT_S1, &accel[0][0]);	
	ecrobot_get_accel_sensor(NXT_PORT_S2, &accel[1][0]);	
	sonarS3 = ecrobot_get_sonar_sensor(NXT_PORT_S3);
	sonarS4 = ecrobot_get_sonar_sensor(NXT_PORT_S4);
	
 	TerminateTask();
}

TASK(Task2)
{
	while(1)
	{
		display_clear(0);

		display_goto_xy(0, 0);
		display_string("Multiple I2Cs");
 
 		display_goto_xy(0, 1);
		display_string("S1 X/Y: ");
		display_int(accel[0][0], 0);
		display_int(accel[0][1], 5);
 		display_goto_xy(0, 2);
		display_string("S1   Z: ");
		display_int(accel[0][2], 0);

 		display_goto_xy(0, 3);
		display_string("S2 X/Y: ");
		display_int(accel[1][0], 0);
		display_int(accel[1][1], 5);
 		display_goto_xy(0, 4);
		display_string("S2   Z: ");
		display_int(accel[1][2], 0);

 		display_goto_xy(0, 5);
		display_string("SonarS3: ");
		display_int(sonarS3, 0);

		display_goto_xy(0, 6);
		display_string("SonarS4: ");
		display_int(sonarS4, 0);

		display_update();
		
		systick_wait_ms(100);
	}
}
