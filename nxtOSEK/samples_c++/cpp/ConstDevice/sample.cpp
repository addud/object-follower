/* sample.cpp for TOPPERS/ATK(OSEK) */ 

#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;

#include "ConstDevice.h"


extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;
	Lcd lcd;

// These non-constant accesses cause compilation errors
//	crLight.setLamp(true);
//	crMic.setDBA(true);
//	crMotorA.setPWM(100);

	while(1)
	{
		lcd.clear();
		lcd.putf("sn",  "Const Devices");
		lcd.putf("sdn", "Light: ", crLight.getBrightness(),0);
		lcd.putf("sdn", "Sonar: ", crSonar.getDistance(),0);
		lcd.putf("sdn", "Sound: ", crMic.getLevel(),0);
		lcd.putf("sdn", "Touch: ", crTouch.isPressed(),0);
		lcd.putf("sd",  "Count: ", crMotorA.getCount(),0);
		lcd.disp();  

		clock.wait(100);
	}
}
}
