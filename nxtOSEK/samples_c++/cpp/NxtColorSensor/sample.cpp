/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "Nxt.h"
#include "Lcd.h"
#include "NXTColorSensor.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* TOPPERS/ATK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(AlarmTask2);
DeclareEvent(EventTask2);

NxtColorSensor color(PORT_1); // default sensor mode: COLORSENSOR

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	(void)SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
}

TASK(Task2)
{
	Nxt nxt;
	Lcd lcd;
	bool entr;
	bool entr_state = false;
	while(1)
	{
		WaitEvent(EventTask2);
        ClearEvent(EventTask2);

		// switching the color sensor mode
        entr = (bool)(nxt.getButtons() & Nxt::ENTR_ON);
		if (entr && !entr_state)
		{
			switch(color.getSensorMode())
			{
				case NxtColorSensor::_COLORSENSOR:
					color.setSensorMode(NxtColorSensor::_LIGHTSENSOR_RED);
					break;
				case NxtColorSensor::_LIGHTSENSOR_RED:
					color.setSensorMode(NxtColorSensor::_LIGHTSENSOR_GREEN);
					break;
				case NxtColorSensor::_LIGHTSENSOR_GREEN:
					color.setSensorMode(NxtColorSensor::_LIGHTSENSOR_BLUE);
					break;
				case NxtColorSensor::_LIGHTSENSOR_BLUE:
					color.setSensorMode(NxtColorSensor::_LIGHTSENSOR_WHITE);
					break;
				case NxtColorSensor::_LIGHTSENSOR_WHITE:
					color.setSensorMode(NxtColorSensor::_LIGHTSENSOR_NONE);
					break;
				case NxtColorSensor::_LIGHTSENSOR_NONE:
					color.setSensorMode(NxtColorSensor::_DEACTIVATE);
					break;
				case NxtColorSensor::_DEACTIVATE:
					color.setSensorMode(NxtColorSensor::_COLORSENSOR);
					break;
				default:
					// do nothing
					break;
			}
		}
		entr_state = entr;

		// display different sensor data depending on the sensor mode
		lcd.clear();
		switch(color.getSensorMode())
		{
			case NxtColorSensor::_COLORSENSOR:
				lcd.putf("s\n", "COLOR");
				switch(color.getColorNumber())
				{
					case NxtColorSensor::_BLACK:
						lcd.putf("s", "BLACK");
						break;
					case NxtColorSensor::_BLUE:
						lcd.putf("s", "BLUE");
						break;
					case NxtColorSensor::_GREEN:
						lcd.putf("s", "GREEN");
						break;
					case NxtColorSensor::_YELLOW:
						lcd.putf("s", "YELLOW");
						break;
					case NxtColorSensor::_ORANGE:
						lcd.putf("s", "ORANGE");
						break;
					case NxtColorSensor::_RED:
						lcd.putf("s", "RED");
						break;
					case NxtColorSensor::_WHITE:
						lcd.putf("s", "WHITE");
						break;
					default:
						lcd.putf("s", "UNKNOWN COLOR");
						break;
				}
				S16 rgb[3];
				color.getRawColor(rgb);
				lcd.putf("\nsd\nsd\nsd", "R:", rgb[0],0, "G:", rgb[1],0, "B:", rgb[2],0);
				break;
			case NxtColorSensor::_LIGHTSENSOR_RED:
				lcd.putf("s\nd", "LIGHT RED", color.get(),0);
				break;
			case NxtColorSensor::_LIGHTSENSOR_GREEN:
				lcd.putf("s\nd", "LIGHT GREEN", color.get(),0);
				break;
			case NxtColorSensor::_LIGHTSENSOR_BLUE:
				lcd.putf("s\nd", "LIGHT BLUE", color.get(),0);
				break;
			case NxtColorSensor::_LIGHTSENSOR_WHITE:
				lcd.putf("s\nd", "LIGHT WHITE", color.get(),0);
				break;
			case NxtColorSensor::_LIGHTSENSOR_NONE:
				lcd.putf("s\nd", "LIGHT OFF", color.get(),0);
				break;
			case NxtColorSensor::_DEACTIVATE:
				lcd.putf("s", "SENSOR OFF");
				break;
			default:
				lcd.putf("INVALID MODE");
				break;
		}
		lcd.cursor(0,6);
		lcd.putf("s\ns", "================",
				         "ENTR:CHANGE MODE");
		lcd.disp();
	}
}

TASK(Task1)
{
	SetRelAlarm(AlarmTask2, 1, 100); // set event for Task2 by Alarm
	while(1)
	{
		color.processBackground(); // communicates with NXT Color Sensor (this must be executed repeatedly in a background Task)
	}
}
}
