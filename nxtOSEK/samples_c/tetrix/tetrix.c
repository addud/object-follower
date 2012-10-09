/* tetrix.c */
/***************************************************
Exemple with Tetrix:
-Read Tetrix Battery voltage.
-Send random power on motors and random positions on servos. 

Daisy chain configuration used in this example:
   __________      __________       ______
  | servo    |    | dc motor |     |       |
  | ctrller  |    | ctrller  |     |  NXT  |
  |__________|    |__________|     |_____ _|
    |     |__________|     |________| | | |
				   S1	
-> Adress 2          Address 1

Loic Cuvillon
based on an exemple for NXC by Matthew Richardson. 
**************************************************/

 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include <stdlib.h>

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);


/* LEJOS OSEK hooks */

void ecrobot_device_initialize(void)
{
ecrobot_init_tetrix(NXT_PORT_S2);
}


void ecrobot_device_terminate()
{
ecrobot_term_tetrix(NXT_PORT_S1);
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
	
	S32 millivolt=0;
	S8 power1, power2;
	U8 servo1, servo2, servo3, servo4, servo5, servo6;

	power1 = (rand()%(200) )-100 ;
	power2 = (rand()%(200) )-100 ;
	
	servo1= (rand()%(200) )+27 ;
	servo2= (rand()%(200) )+27 ;
	servo3=servo4=servo5=servo6=0;
	

	millivolt=ecrobot_tetrix_battery(NXT_PORT_S1, TETRIX_ADDRESS_1);

	ecrobot_tetrix_motors(NXT_PORT_S1, TETRIX_ADDRESS_1,
				 TETRIX_MODE_PWM, TETRIX_MODE_PWM_REV,
				power1, power2);


	ecrobot_tetrix_servos(NXT_PORT_S1, TETRIX_ADDRESS_2,
				TETRIX_SERVO_NO_STEP_TIME,TETRIX_SERVO_ON,
				 servo1,servo2,servo3,servo4,servo5,servo6);


	/*Display of the batery and command signal values */
	display_clear(0);
	display_goto_xy(0,0);

	display_string("Batt:");
	display_int(millivolt, 0);

	display_goto_xy(0, 1);
	display_string("Power 1:");
	display_int(power1, 0);

	display_goto_xy(0, 2);
	display_string("Power 2:");
	display_int(power2, 0);

	display_goto_xy(0, 3);
	display_string("Servo 1:");
	display_int(servo1, 0);

	display_goto_xy(0, 4);
	display_string("Servo 2:");
	display_int(servo2, 0);




	display_update();



	TerminateTask();
}

