/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "Nxt.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Nxt nxt;
	Lcd lcd;
	Clock clock;

	U32 startTime = clock.now();
	while(1)
	{
		lcd.clear();
		lcd.putf("sn",  "NXT BIOS will be");
		lcd.putf("sn",  "executed after");
		lcd.putf("snn", "10 seconds");

		U32 currentTime = (clock.now() - startTime)/1000;
		lcd.putf("sdn", "Elapsed time: ", currentTime,0);

		lcd.putf("snn", "================");
		lcd.putf("s",   "      EXIT      ");
		lcd.disp();

		if (currentTime >= 10)
		{
			nxt.execNXTBIOS();
		}

		if (nxt.getNxtButtons() & Nxt::GRAY_RECT)
		{
			nxt.shutdown();
		}

		clock.wait(100);
	}
}
}
