/* nxtcolorsensortest.c */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


#define PORT_ID NXT_PORT_S1

/* TOPPERS/ATK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(AlarmTask2);
DeclareEvent(EventTask2);

/* nxtOSEK hooks */
void ecrobot_device_initialize(void)
{
	ecrobot_init_nxtcolorsensor(PORT_ID, NXT_COLORSENSOR); // initialize a sensor
}

void ecrobot_device_terminate(void)
{
	ecrobot_term_nxtcolorsensor(PORT_ID); // terminate a sensor
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	(void)SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
}

/* Alarm executed Task2 */
TASK(Task2)
{
	U8 entr;
	U8 entr_state = 0;
	while(1)
	{
		WaitEvent(EventTask2);
        ClearEvent(EventTask2);

		// switching the color sensor mode
		entr = ecrobot_is_ENTER_button_pressed();
		if (entr && !entr_state)
		{
			switch(ecrobot_get_nxtcolorsensor_mode(PORT_ID))
			{
				case NXT_COLORSENSOR:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_LIGHTSENSOR_RED);
					break;
				case NXT_LIGHTSENSOR_RED:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_LIGHTSENSOR_GREEN);
					break;
				case NXT_LIGHTSENSOR_GREEN:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_LIGHTSENSOR_BLUE);
					break;
				case NXT_LIGHTSENSOR_BLUE:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_LIGHTSENSOR_WHITE);
					break;
				case NXT_LIGHTSENSOR_WHITE:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_LIGHTSENSOR_NONE);
					break;
				case NXT_LIGHTSENSOR_NONE:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_COLORSENSOR_DEACTIVATE);
					break;
				case NXT_COLORSENSOR_DEACTIVATE:
					ecrobot_set_nxtcolorsensor(PORT_ID, NXT_COLORSENSOR);
					break;
				default:
					// do nothing
					break;
			}
		}
		entr_state = entr;

		// display different sensor data depending on the sensor mode
		display_clear(0);
		display_goto_xy(0, 0);
		switch(ecrobot_get_nxtcolorsensor_mode(PORT_ID))
		{
			case NXT_COLORSENSOR:
				display_string("COLOR");
				display_goto_xy(0, 1);
				switch(ecrobot_get_nxtcolorsensor_id(PORT_ID)) // get color number data
				{
					case NXT_COLOR_BLACK:
						display_string("BLACK");
						break;
					case NXT_COLOR_BLUE:
						display_string("BLUE");
						break;
					case NXT_COLOR_GREEN:
						display_string("GREEN");
						break;
					case NXT_COLOR_YELLOW:
						display_string("YELLOW");
						break;
					case NXT_COLOR_ORANGE:
						display_string("ORANGE");
						break;
					case NXT_COLOR_RED:
						display_string("RED");
						break;
					case NXT_COLOR_WHITE:
						display_string("WHITE");
						break;
					default:
						display_string("UNKNOWN COLOR");
						break;
				}
				S16 rgb[3];
				ecrobot_get_nxtcolorsensor_rgb(PORT_ID, rgb); // get rgb data
				display_goto_xy(0, 2);
				display_string("R:");
				display_int(rgb[0],0);
				display_goto_xy(0, 3);
				display_string("G:");
				display_int(rgb[1],0);
				display_goto_xy(0, 4);
				display_string("B:");
				display_int(rgb[2],0);
				break;
			case NXT_LIGHTSENSOR_RED:
				display_string("LIGHT RED");
				display_goto_xy(0, 1);
				display_int(ecrobot_get_nxtcolorsensor_light(PORT_ID), 0); // get light sensor data
				break;
			case NXT_LIGHTSENSOR_GREEN:
				display_string("LIGHT GREEN");
				display_goto_xy(0, 1);
				display_int(ecrobot_get_nxtcolorsensor_light(PORT_ID), 0); // get light sensor data
				break;
			case NXT_LIGHTSENSOR_BLUE:
				display_string("LIGHT BLUE");
				display_goto_xy(0, 1);
				display_int(ecrobot_get_nxtcolorsensor_light(PORT_ID), 0); // get light sensor data
				break;
			case NXT_LIGHTSENSOR_WHITE:
				display_string("LIGHT WHITE");
				display_goto_xy(0, 1);
				display_int(ecrobot_get_nxtcolorsensor_light(PORT_ID), 0); // get light sensor data
				break;
			case NXT_LIGHTSENSOR_NONE:
				display_string("LIGHT NONE");
				display_goto_xy(0, 1);
				display_int(ecrobot_get_nxtcolorsensor_light(PORT_ID), 0); // get light sensor data
				break;
			case NXT_COLORSENSOR_DEACTIVATE:
				display_string("SENSOR OFF");
				break;
			default:
				display_string("INVALID MODE");
				break;
		}
		display_goto_xy(0, 6);
		display_string("================");
		display_goto_xy(0, 7);
		display_string("ENTR:CHANGE MODE");
		display_update();
	}
}

/* Background Task */
TASK(Task1)
{
	SetRelAlarm(AlarmTask2, 1, 100); // set event for Task2 by Alarm
	while(1)
	{
		ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color Sensor (this must be executed repeatedly in a background Task)
	}
}
