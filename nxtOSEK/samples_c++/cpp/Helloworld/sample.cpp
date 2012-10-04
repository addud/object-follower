/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void){}

TASK(TaskMain)
{
	Lcd lcd;

	lcd.clear();
	lcd.putf("s", "Hello World");
	lcd.disp();

	while(1);
}
}
