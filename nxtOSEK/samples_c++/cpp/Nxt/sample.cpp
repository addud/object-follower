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

	while(1)
	{
		bool entrBtn = (bool)(nxt.getButtons() & Nxt::ENTR_ON);
		bool  runBtn = (bool)(nxt.getButtons() & Nxt::RUN_ON);
  
		lcd.clear();
		lcd.putf("snn",   "Nxt");
		lcd.putf("sdnsdn", "Time[sec]: ", clock.now()/1000,0, "Batt[mV]:  ", nxt.getBattMv(),0); 
		lcd.putf("sdnsd",  "ENTR btn:  ", entrBtn,0, "RUN btn:   ", runBtn,0); 
		lcd.disp();

		clock.wait(100);
	}
}
}
