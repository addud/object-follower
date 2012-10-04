/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "Bluetooth.h"
#include "Lcd.h"
#include "Nxt.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Bluetooth bt;

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

TASK(TaskMain)
{
	Lcd lcd;
	Nxt nxt;

	lcd.clear();
	lcd.putf("sn", "Press ENTR to");
	lcd.putf("s" , "reset BT.");
	lcd.disp();

	while(!(nxt.getButtons() & Nxt::ENTR_ON));

	bt.setFactorySettings();

	lcd.clear();
	lcd.putf("sn", "BT was reset.");
	lcd.putf("sn", "Turn off the NXT");
	lcd.putf("sn", " and");
	lcd.putf("s", "Remove battery.");
	lcd.disp();
	
	while(1);
}
}
