/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "LegoLight.h"
#include "RcxLightSensor.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

RcxLightSensor rcxLightSensor(PORT_1);
LegoLight legoLight(PORT_A);

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Lcd lcd;
	Nxt nxt;
	Clock clock;

	while(1)
	{
		if (nxt.getButtons() & Nxt::ENTR_ON)
		{
			legoLight.turnOn();
		}
		else
		{
			legoLight.turnOff();
		}
		
		lcd.clear();
		lcd.putf("sn", "Misc. devices");
		lcd.putf("sd", "RCX light: ", rcxLightSensor.getBrightness(),0);
		lcd.disp();
		
		clock.wait(50);
	}
}
}
