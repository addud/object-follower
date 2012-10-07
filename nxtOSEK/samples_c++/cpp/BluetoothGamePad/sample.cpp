/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "Clock.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Vector.h"
#include "GamePad.h" // GamePad class for NXT GamePad
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
	Clock clock;
	Lcd lcd;
	Nxt nxt;
	BTConnection btConnection(bt, lcd, nxt);

	if (btConnection.connect(PASSKEY) == 1)
	{
		GamePad gp(bt);
		VectorT<S8> command;
		lcd.clear();
		lcd.putf("s", "GamePad");
		while(1)
		{
			command = gp.get(); // receive command from GamePad
			lcd.clearRow(1); // clear data buffer at row 1
			lcd.putf("dd", command.mX,0, command.mY,5);
			lcd.disp();

			clock.wait(50);
		}
	}
	while(1);
}
}
