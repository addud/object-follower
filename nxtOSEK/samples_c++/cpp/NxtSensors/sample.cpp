/* sample.cpp for TOPPERS/ATK(OSEK) */ 

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

LightSensor  light(PORT_1, false /* lamp off */);
SonarSensor  sonar(PORT_2);
SoundSensor    mic(PORT_3);
TouchSensor  touch(PORT_4);

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;
	Lcd lcd;

	while(1)
	{
		lcd.clear();
		lcd.putf("sn",   "NXT Sensors");
		lcd.putf("sddn", "1/2: ", light.getBrightness(),0, sonar.getDistance(),5);
		lcd.putf("sdd",  "3/4: ", mic.getLevel(),0, touch.isPressed(),5);
		lcd.disp();  

		clock.wait(100);
	}
}
}
