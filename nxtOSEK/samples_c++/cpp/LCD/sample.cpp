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


// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Lcd lcd;
	Clock clock;

	while(1)
	{
		// LCD display should be:
		//
		// Top
		// 0123456789ABCDEF
		// Calc: 16-1=0xF
		//                A
		// Digit  1000
		// -1000 Signed
		// FF Hex
		// Bottom  
		lcd.clear();
		lcd.cursor(0, Lcd::MAX_CURSOR_Y);
		lcd.putf("snsn", "Bottom", "Top");
		lcd.putf("sn",   "0123456789ABCDEFG"); // G is cut off
		lcd.putf("sddsx", "Calc: ", 16,0, -1,2, "=0x", (16-1),0);
		lcd.cursor(Lcd::MAX_CURSOR_X, 3);
		lcd.putf("s", "AB"); // B is cut off 
		lcd.putf("nsdndsnxs", "Digit ", 1000,5, -1000,0, " Signed", 255,2, " Hex");
		lcd.disp();

		clock.wait(100);
	}
}
}
