/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "Motor.h"
#include "Nxt.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Motor motorA(PORT_A); // brake by defalut
Motor motorB(PORT_B); // brake by defalut
Motor motorC(PORT_C, false); // float 

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Nxt nxt;
	Clock clock;
	Lcd lcd;

	motorB.setBrake(false); // float (brake off)
	
	while(1)
	{
		if (nxt.getButtons() == Nxt::ENTR_ON)
		{
			motorA.setPWM(0);   // pwm=0 and count=0
			motorA.setCount(0); 
			motorB.setPWM(0);   // pwm=0 and count=0
			motorB.setCount(0); 
			motorC.setCount(0); // count = 0
		}
		else
		{	
			motorA.setPWM(100);
			motorB.setPWM(100);
		}
		
		lcd.clear();
		lcd.putf("sn",   "Motor");
		lcd.putf("sddn", "A/B:", motorA.getCount(),0, motorB.getCount(),5);
		lcd.putf("sd",   "C:  ", motorC.getCount(),0);
		lcd.disp();

		clock.wait(100);
	}
}
}
