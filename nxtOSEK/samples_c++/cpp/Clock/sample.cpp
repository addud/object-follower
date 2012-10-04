/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Lcd lcd;
Clock clock;

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(Task1)
{
	lcd.clear();
	lcd.putf("s", "Clock");
	clock.reset();

	while(1)
	{
		lcd.cursor(0, 2);
		lcd.putf("sd", "Task1: ", clock.now(),8);
		lcd.disp();

		clock.sleep(1000); // sleep 1sec
	}
}

TASK(Task2)
{
	while(1)
	{
		lcd.cursor(0, 3);
		lcd.putf("sd", "Task2: ", clock.now(),8);

		clock.sleep(2000); // sleep 2sec
	}
}

TASK(Task3)
{
	while(1)
	{
		lcd.cursor(0, 4);
		lcd.putf("sd", "Task3: ", clock.now(),8);

		clock.sleep(3000); // sleep 3sec
	}
}

}
