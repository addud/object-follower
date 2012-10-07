/* hitechtest.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define S_PORT_ID   (NXT_PORT_S1)
#define SAMPLING_RATE (50) // msec

#ifdef DIGITAL_OUT
	#define DIGITAL_DIR   HTPS_DIGTAL_PORTS
#else
	#define DIGITAL_DIR   (0x00)
#endif

/* nxtOSEK hooks */
void ecrobot_device_initialize(void)
{
	ecrobot_init_prototype_sensor(S_PORT_ID, SAMPLING_RATE, DIGITAL_DIR);
}

void ecrobot_device_terminate(void)
{
	ecrobot_term_prototype_sensor(S_PORT_ID);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

/* Background Task */
TASK(Task1)
{
	while(1)
	{
		display_clear(0);
		display_goto_xy(0, 0);

#ifdef ANALOG_IN
		display_string("ANALOG IN TEST");
		S16 buf[5];
		ecrobot_get_prototype_analog_sensor(S_PORT_ID, buf);

		display_goto_xy(0, 1);
		display_string("AI0: ");
		display_int(buf[0], 0);

		display_goto_xy(0, 2);
		display_string("AI1: ");
		display_int(buf[1], 0);

		display_goto_xy(0, 3);
		display_string("AI2: ");
		display_int(buf[2], 0);

		display_goto_xy(0, 4);
		display_string("AI3: ");
		display_int(buf[3], 0);

		display_goto_xy(0, 5);
		display_string("AI4: ");
		display_int(buf[4], 0);
#elif DIGITAL_IN
		display_string("DIGITAL IN TEST");
		U8 buf = ecrobot_get_prototype_digital_sensor(S_PORT_ID);

		display_goto_xy(0, 1);
		display_string("DI0: ");
		display_int((U8)(HTPS_D0 == (buf&HTPS_D0)), 0);

		display_goto_xy(0, 2);
		display_string("DI1: ");
		display_int((U8)(HTPS_D1 == (buf&HTPS_D1)), 0);

		display_goto_xy(0, 3);
		display_string("DI2: ");
		display_int((U8)(HTPS_D2 == (buf&HTPS_D2)), 0);

		display_goto_xy(0, 4);
		display_string("DI3: ");
		display_int((U8)(HTPS_D3 == (buf&HTPS_D3)), 0);

		display_goto_xy(0, 5);
		display_string("DI4: ");
		display_int((U8)(HTPS_D4 == (buf&HTPS_D4)), 0);

		display_goto_xy(0, 6);
		display_string("DI5: ");
		display_int((U8)(HTPS_D5 == (buf&HTPS_D5)), 0);
#elif DIGITAL_OUT
		display_string("DIGITAL OUT TEST");

		display_goto_xy(0, 1);
		if (ecrobot_is_ENTER_button_pressed())
		{
			ecrobot_send_prototype_digital_sensor(S_PORT_ID, HTPS_DIGTAL_PORTS); // all digital ports are on
			display_string("DO:1");
		}
		else
		{
			ecrobot_send_prototype_digital_sensor(S_PORT_ID, 0x00); // all digital ports are off
			display_string("DO:0");
		}

#endif

		display_update();
   		systick_wait_ms(SAMPLING_RATE);
	}
}
