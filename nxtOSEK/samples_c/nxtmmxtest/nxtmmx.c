/* nxtmmx.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define MMX_I2C_ADDR 			0x03
#define NXT_PORT  				NXT_PORT_S1
#define wait					1
#define motorbrake				1
#define motorfloat				0
#define three_rev				3*360
#define run_relative			1
#define run_absolute			0

U32 count = 0;
/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
	ecrobot_MMX_init(NXT_PORT);
}

void ecrobot_device_terminate()
{
	ecrobot_term_MMX(NXT_PORT);
}

void user_1ms_isr_type2(void){}

/* TaskControl executed every 10msec */
TASK(OSEK_Task_Background)
{

	S8 speed1 = 60;
	S8 speed2 = -40;
//	U8 data[4];
//    S32 count = 0;
	U8 motorstatus = 0;
	//ecrobot_set_MMX_speed(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_1, 0, 0);
	//ecrobot_set_MMX_speed(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_2, 0, 0);

	while(1)
	{

		if (ecrobot_is_RUN_button_pressed())
		{
			ecrobot_set_MMX_time(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_1, speed1, 10, motorbrake);
			//ecrobot_set_MMX_speed(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_2, speed1,0);
			ecrobot_set_MMX_Run_Rev(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_2, speed1, three_rev, run_relative, motorbrake);
			display_clear(0);
			display_goto_xy(0, 0);
			display_string("NXTMMX Test");

			//display_update();
		}

		if (ecrobot_is_ENTER_button_pressed())
		{
			ecrobot_set_MMX_speed(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_2, speed2,0);
			display_clear(0);
			display_goto_xy(0, 0);
			display_string("MMX_Motor_1 run reverse");
			display_goto_xy(0, 1);
			display_update();
		}

		motorstatus = MMX_MotorStatus(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_1);
		//count = ecrobot_get_MMX_count(NXT_PORT, MMX_I2C_ADDR, MMX_Motor_1);
		display_goto_xy(0, 1);
		display_hex(motorstatus,0);
		//display_goto_xy(0, 2);
		//display_int(count, 0);
		display_update();

	}
	systick_wait_ms(10); /* 10msec wait */
  	TerminateTask();
}

