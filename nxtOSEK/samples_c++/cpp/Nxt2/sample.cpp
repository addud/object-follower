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

	int count = 0;
	while(1)
	{
		lcd.clear();
		lcd.putf("snn", "Nxt");
		Nxt::eNxtButton bttns = nxt.getNxtButtons();
		lcd.putf("sdn", "Orange rect:", static_cast<int>((bttns & Nxt::ORANGE_RECT) != 0),0);
		lcd.putf("sdn", "Left triangle:", static_cast<int>((bttns & Nxt::LEFT) != 0),0);
		lcd.putf("sdn", "Right triangle:", static_cast<int>((bttns & Nxt::RIGHT) != 0),0);
		lcd.putf("sdn", "Gray rect:", static_cast<int>((bttns & Nxt::GRAY_RECT) != 0),0);
		lcd.putf("sdnsdn", "Time[sec]:", clock.now()/1000,0, "Batt[mV]:", nxt.getBattMv(),0);
		lcd.disp();

		if (bttns & Nxt::GRAY_RECT)
		{
			// Keep pressing the gray rectangle button for longer than 1 second to shutdown the NXT
			if (count++ >= 10)
			{
				nxt.shutdown();
			}
		}
		else
		{
			count = 0;
		}

		clock.wait(100);
	}
}
}
