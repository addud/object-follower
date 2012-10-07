/* hitechtest.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hooks */
void ecrobot_device_initialize(void)
{
	ecrobot_init_i2c(NXT_PORT_S1, LOWSPEED);
	ecrobot_init_i2c(NXT_PORT_S2, LOWSPEED);
	ecrobot_init_i2c(NXT_PORT_S3, LOWSPEED);
}

void ecrobot_device_terminate(void)
{
	ecrobot_term_i2c(NXT_PORT_S1);
	ecrobot_term_i2c(NXT_PORT_S2);
	ecrobot_term_i2c(NXT_PORT_S3);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

void TestIRSeeker(U8 port_id)
{
	S8 data[6];

	ecrobot_get_ir_seeker(port_id, data);

	display_goto_xy(0, 0);
	display_string("IR SEEKER TEST");

	display_goto_xy(0, 1);
	display_string("DIR: ");
	display_int(data[0], 0);

	display_goto_xy(0, 2);
	display_string("INT1/2: ");
	display_int(data[1], 0);
	display_int(data[2], 5);

	display_goto_xy(0, 3);
	display_string("INT3/4: ");
	display_int(data[3], 0);
	display_int(data[4], 5);

	display_goto_xy(0, 4);
	display_string("INT5: ");
	display_int(data[5], 0);
}

void TestColorSensor(U8 port_id)
{
	S16 data[3];

	ecrobot_get_color_sensor(port_id, data);

	display_goto_xy(0, 0);
	display_string("COLOR TEST");

	display_goto_xy(0, 1);
	display_string("R: ");
	display_int(data[0], 0);

	display_goto_xy(0, 2);
	display_string("G: ");
	display_int(data[1], 0);

	display_goto_xy(0, 3);
	display_string("B: ");
	display_int(data[2], 0);
}

void TestCompassSensor(U8 port_id)
{
	display_goto_xy(0, 0);
	display_string("COMPASS TEST");

	display_goto_xy(0, 1);
	display_string("HEADING: ");
	display_int(ecrobot_get_compass_sensor(port_id), 0);
}

/* Background Task */
TASK(Task1)
{
#ifdef COMPASS
//	ecrobot_cal_compass_sensor(NXT_PORT_S3); /* optional API */
#endif

	while(1)
	{
		display_clear(0);

#ifdef IR_SEEKER
		TestIRSeeker(NXT_PORT_S1);
#elif COLOR
		TestColorSensor(NXT_PORT_S2);
#elif COMPASS
		TestCompassSensor(NXT_PORT_S3);
#endif

		display_update();
   		systick_wait_ms(100);
	}
}
