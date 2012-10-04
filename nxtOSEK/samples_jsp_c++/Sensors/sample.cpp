/* sample.cpp for TOPPERS/JSP(ITRON) */ 

// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "SoundSensor.h"
#include "TouchSensor.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

TouchSensor  touch(PORT_1);
SonarSensor  sonar(PORT_2);
LightSensor  light(PORT_3, true /* lamp off */);

void jsp_systick_low_priority(void)
{
	if (get_OS_flag()) /* check whether JSP already started or not */
	{
		isig_tim();          /* cyclic task dispatcher */
		check_NXT_buttons();
	}
}

void tsk(VP_INT exinf)
{
	Clock clock;
	Lcd lcd;

	while(1)
	{
		lcd.clear();
		lcd.putf("snn",  "NXT Sensors");
		lcd.putf("sdn",  " Sonar: ", sonar.getDistance(),5);
		lcd.putf("sdn",  " Light: ", light.getBrightness(),5);
		lcd.putf("sd",   " Touch: ", touch.isPressed(),5);
		lcd.disp();

		clock.wait(100);
	}
}
}
