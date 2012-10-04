/* cal_hitechcolor.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define PORT_ID NXT_PORT_S2

/* nxtOSEK hooks */
void ecrobot_device_initialize(void)
{
	ecrobot_init_i2c(PORT_ID, LOWSPEED);
}

void ecrobot_device_terminate(void)
{
	ecrobot_term_i2c(PORT_ID);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

void TestColorSensor(U8 port_id)
{
	S16 data[3];

	ecrobot_get_color_sensor(port_id, data);

	display_clear(0);
	display_goto_xy(0, 0);
	display_string("RAW COLOR VAL");

	display_goto_xy(0, 1);
	display_string("R: ");
	display_int(data[0], 0);

	display_goto_xy(0, 2);
	display_string("G: ");
	display_int(data[1], 0);

	display_goto_xy(0, 3);
	display_string("B: ");
	display_int(data[2], 0);
	display_update();
}

/* Background Task */
TASK(Task1)
{
	U8 entr;

	display_clear(0);
	display_goto_xy(0, 0);
	display_string("READ README.TXT");
	display_goto_xy(0, 1);
	display_string("ENTR: CAL WHITE");
	display_update();

	while(!ecrobot_is_ENTER_button_pressed());
	ecrobot_cal_color_sensor(PORT_ID, CAL_WHITE);

	display_goto_xy(0, 2);
	display_string("...DONE");

	display_goto_xy(0, 3);
	display_string("ENTR: CAL BLACK");
	display_update();

	while(1)
	{
		entr =  ecrobot_is_ENTER_button_pressed();
		if (!entr && ecrobot_is_ENTER_button_pressed()) break;
	}
	ecrobot_cal_color_sensor(PORT_ID, CAL_BLACK);

	display_goto_xy(0, 4);
	display_string("...DONE");
	display_goto_xy(0, 5);
	display_string("WAIT...");
	display_update();

	systick_wait_ms(1000);

	while(1)
	{
		TestColorSensor(PORT_ID);
   		systick_wait_ms(100);
	}
}
