/**
 *  nxte_test.c 
 * 
 * This is a sample program for LATTEBOX NXTe(NXT Extension Kit Product)
 * and LSC22(22-Axis Servo Kit Product)
 * <http://www.lattebox.com/product_list_e.php?pts_type=1>
 * 
 * It enables a NXT to control RC servo motors via I2C.
 * Maximum number of RC servos to be controlled is:
 * Number of NXT Sensor ports(4) * Number of NXTe channels (4) * Number of LSC22 channels (22)
 * = 352 RC Servos might be controlled by using a NXT!
 * 
 * Special thanks to Yu Yang <sog@lattebox.com>
 */ 
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "nxte22.h"

/* OSEK declarations */
DeclareTask(Task1);

/* NXT Sensor port configration */
#define NXT_PORT  NXT_PORT_S3

/* LATTEBOX NXTe channel configuration */
#define CH1 1 /* channel 0 to 3 */

/* LATTEBOX LSC servo channel configuration */  
#define SERVO_CH 0 /* servo channels: 0 to 21 */

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_i2c(NXT_PORT, LOWSPEED_9V);
}

void ecrobot_device_terminate()
{
	ecrobot_term_i2c(NXT_PORT);
}

void user_1ms_isr_type2(void){}


TASK(Task1)
{
	init_NXTe22(NXT_PORT);
	sync_NXTe22Servo(NXT_PORT, NXTe_CH[CH1]);
	load_NXTe22Servo(NXT_PORT, NXTe_CH[CH1], ALL_22SERVO_ENABLE);
	set_NXTe22Delay(NXT_PORT, NXTe_CH[CH1], SERVO_CH, 0); 

	display_goto_xy(0, 0);
	display_string("NXTe22 Test");
	display_update();
	while(1)
	{
		if (ecrobot_is_RUN_button_pressed())
		{
			set_NXTe22Angle(NXT_PORT, NXTe_CH[CH1], SERVO_CH, MAX_ANGLE);
			while(read_NXTe22Motion(NXT_PORT, NXTe_CH[CH1]) != 0);
			display_clear(0);
			display_goto_xy(0, 0);
			display_string("NXTe22 Test");
			display_goto_xy(0, 1);
			display_int(get_NXTe22Angle(NXT_PORT, NXTe_CH[CH1], SERVO_CH), 0);
			display_update();
		}
		
		if (ecrobot_is_ENTER_button_pressed())
		{
			set_NXTe22Angle(NXT_PORT, NXTe_CH[CH1], SERVO_CH, MIN_ANGLE);
			while(read_NXTe22Motion(NXT_PORT, NXTe_CH[CH1]) != 0);
			display_clear(0);
			display_goto_xy(0, 0);
			display_string("NXTe22 Test");
			display_goto_xy(0, 1);
			display_int(get_NXTe22Angle(NXT_PORT, NXTe_CH[CH1], SERVO_CH), 0);
			display_update();
		}
	}	
   	
	TerminateTask();
}
