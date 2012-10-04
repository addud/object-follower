/* speedtest.c */ 
#include <stdlib.h> 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */
DeclareTask(Task1);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_sonar_sensor(NXT_PORT_S4);	
}
void ecrobot_device_terminate()
{
	ecrobot_term_sonar_sensor(NXT_PORT_S4);	
}
void user_1ms_isr_type2(void){}

/* Sub functions */
int getRandom(int min, int max)
{
	return min + (int)((double)rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

/* 
 * LEJOS OSEK V1.07 has an interrupt based LCD display feature thanks to LEJOS NXJ develpment team.
 * Therefore, LCD display performance is dramatically improved. Actually, LCD update is too
 * fast to see. The purpose of this speed test is to measure the performance of LEJOS OSEK under
 * a common program load compared to other programming languages. (The maximum LCD refresh rate
 * on hardware level is 60Hz, so faster refresh rate than 60Hz has no meaning in practical use.)
 * So the result could be seen only at the end of the test
 */
void disp(int row, char *str, int val)
{
#define DISPLAY_ON
#ifdef DISPLAY_ON 
	display_clear(0);
	display_goto_xy(0, row);
	display_string(str);
	display_int(val, 0);
	display_update();
#endif
}

/* Task for speed test */
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
		disp(0, " ADC: ", light);							/* Display Light Sensor              */
		sonar = ecrobot_get_sonar_sensor(NXT_PORT_S4); 		/* Read US Sensor                    */
		disp(1, " I2C: ", sonar);							/* Display US Sensor                 */
		rev = nxt_motor_get_count(NXT_PORT_B);	 			/* Read Rotation Sensor              */
		disp(2, " REV: ", rev);								/* Display Rotation Sensor           */
		RN = getRandom(1,100);								/* Get random number (1-100)         */
		disp(3, "  RN: ", RN);								/* Display random number             */
		disp(4, " VAL: ", (light+sonar+rev)*100/RN);		/* Display VAL                       */
		nxt_motor_set_speed(NXT_PORT_B, RN, 1); 			/* Set motor speed for B and C to RN */
		nxt_motor_set_speed(NXT_PORT_C, RN, 1);
    	if(RN > 50) A++;
    	else if(RN < 50) A--;
		disp(5, "   A: ", A);								/* Display A                         */
		nxt_motor_set_speed(NXT_PORT_A, A, 1); 				/* Set motor A speed to A            */
		
		disp(6, "LOOP: ", loop_cnt++);						/* Display loop count                */
		disp(7, "TIME: ", systick_get_ms()/1000);			/* Display time in seconds           */
	} while(systick_get_ms() < time_out);					/* Loop for 60 seconds               */

	nxt_motor_set_speed(NXT_PORT_A, 0, 1);					/* Stop motors                       */
	nxt_motor_set_speed(NXT_PORT_B, 0, 1);
	nxt_motor_set_speed(NXT_PORT_C, 0, 1);

	display_clear(0);

	display_goto_xy(0, 0);
	display_string(" ADC: ");
	display_int(light, 0);

	display_goto_xy(0, 1);
	display_string(" I2C: ");
	display_int(sonar, 0);

	display_goto_xy(0, 2);
	display_string(" REV: ");
	display_int(rev, 0);

	display_goto_xy(0, 3);
	display_string("  RN: ");
	display_int(RN, 0);

	display_goto_xy(0, 4);
	display_string(" VAL: ");
	display_int((light+sonar+rev)*100/RN, 0);

	display_goto_xy(0, 5);
	display_string("   A: ");
	display_int(A, 0);

	display_goto_xy(0, 6);
	display_string("LOOP: ");
	display_int(loop_cnt, 0);

	display_goto_xy(0, 7);
	display_string("TIME: ");
	display_int(systick_get_ms()/1000, 0);

	display_update();

	systick_wait_ms(10000);									/* Show display for 10 seconds       */
	
	TerminateTask();
}
