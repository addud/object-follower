/* speedtest.c */ 
#include <stdlib.h> 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareTask(Task1);

/* OSEK hooks */
void StartupHook(void){}
void ShutdownHook(StatusType ercd){}
void PreTaskHook(void){}
void PostTaskHook(void){}
void ErrorHook(StatusType ercd){}

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_sonar_sensor(NXT_PORT_S2);	
}
void ecrobot_device_terminate()
{
	ecrobot_term_sonar_sensor(NXT_PORT_S2);	
}
void user_1ms_isr_type2(void){}

/* Sub functions */
int getRandom(int min, int max)
{
	return min + (int)((double)rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void disp(int row, char *str, int val)
{ 
	if (row == 0) display_clear(0);
	display_goto_xy(0, row);
	display_string(str);
	display_int(val, 0);
	if (row == 7) display_update();
}
/* Task for speed test
 * If you want to see the performance of LCD display,
 * remove // in the loop
 */
TASK(Task1)
{
	int time_out;
	int light;
	int sonar;
	int rev;
	int RN;
	int A = 0;
	int loop_cnt = 0;
	
	time_out = systick_get_ms() + 60000;

	do {
		light = (int)ecrobot_get_light_sensor(NXT_PORT_S3);	/* Read Light Sensor                 */
//		disp(0, " ADC: ", light);							/* Display Light Sensor              */
		sonar = ecrobot_get_sonar_sensor(NXT_PORT_S2); 		/* Read US Sensor                    */
//		disp(1, " I2C: ", sonar);							/* Display US Sensor                 */
		rev = nxt_motor_get_count(NXT_PORT_B);	 			/* Read Rotation Sensor              */
//		disp(2, " REV: ", rev);								/* Display Rotation Sensor           */
		RN = getRandom(1,100);								/* Get random number (1-100)         */
//		disp(3, "  RN: ", RN);								/* Display random number             */
//		disp(4, " VAL: ", (light+sonar+rev)*100/RN);		/* Display VAL                       */
		nxt_motor_set_speed(NXT_PORT_B, RN, 1); 			/* Set motor speed for B and C to RN */
		nxt_motor_set_speed(NXT_PORT_C, RN, 1);
    	if(RN > 50) A++;
    	else if(RN < 50) A--;
//		disp(5, "   A: ", A);								/* Display A                         */
		nxt_motor_set_speed(NXT_PORT_A, A, 1); 				/* Set motor A speed to A            */
		loop_cnt++;
		
//		disp(6, "TIME: ", systick_get_ms()/1000);			/* Display time in seconds           */
//		disp(7, "LOOP: ", loop_cnt);						/* Display loop count                */
	} while(systick_get_ms() < time_out);					/* Loop for 60 seconds               */

	nxt_motor_set_speed(NXT_PORT_A, 0, 1);					/* Stop motors                       */
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);

	disp(0, " ADC: ", light);								/* Display Light Sensor              */
	disp(1, " I2C: ", sonar);								/* Display US Sensor                 */
	disp(2, " REV: ", rev);									/* Display Rotation Sensor           */
	disp(3, "  RN: ", RN);									/* Display random number             */
	disp(4, " VAL: ", (light+sonar+rev)*100/RN);			/* Display VAL                       */
	disp(5, "   A: ", A);									/* Display A                         */
	disp(6, "TIME: ", systick_get_ms()/1000);				/* Display time in seconds           */
	disp(7, "LOOP: ", loop_cnt);							/* Display loop count                */

	systick_wait_ms(10000);									/* Show display for 10 seconds       */
	
	TerminateTask();
}
