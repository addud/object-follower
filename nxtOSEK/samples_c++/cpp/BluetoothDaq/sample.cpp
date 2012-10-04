/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "Clock.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Daq.h" // DAQ class for NXT GamePad
#include "Bluetooth.h"
#include "BTConnection.h"
using namespace ecrobot;

Bluetooth bt;

static const CHAR* PASSKEY = "1234";

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

TASK(TaskMain)
{
	Lcd lcd;
	Clock clock;
	Nxt nxt;
	BTConnection btConnection(bt, lcd, nxt);

	if (btConnection.connect(PASSKEY) == 1)
	{
		Daq daq(bt);
		S8 dataS08[2] = {0};
		S32 dataS32 = 0;
		lcd.clear();
		lcd.putf("s", "DAQ");
		lcd.disp();
		while(1)
		{
			dataS08[0]++;
			dataS08[1]--;
			dataS32++;
			daq.send(dataS08, dataS32); // send data to NXT GamePad utility on PC

			clock.wait(10);
		}
	}
	while(1);
}
}
