/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "Clock.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Motor.h"
#include "Bluetooth.h"
#include "BTConnection.h"
using namespace ecrobot;

//=============================================================================
// Device objects
Motor motor(PORT_B);
Bluetooth bt;

static const CHAR* PASSKEY = "1234";

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

//=============================================================================
// 1msec timer interrupt hook
void user_1ms_isr_type2(void){}

//=============================================================================
// Main Task
TASK(TaskMain)
{
	Clock clock;
	Lcd lcd;
	Nxt nxt;
	BTConnection btConnection(bt, lcd, nxt);

#ifdef MASTER_DEVICE
	// BD_ADDRESS should be adopt to the connecting slave device's BD_ADDRESS
	static const U8 BD_ADDRESS[7] = {0x00, 0x16, 0x53, 0x04, 0xF1, 0xB3, 0x00};
	btConnection.connect(PASSKEY, BD_ADDRESS);
#elif defined SLAVE_DEVICE
	btConnection.connect(PASSKEY);
#endif

	U8 data;
	U8 runButton;
	while(1)
	{
		bt.receive(&data, 1);
		motor.setPWM(static_cast<S8>(data*100));

		runButton = static_cast<U8>(nxt.getButtons() & Nxt::RUN_ON);
		bt.send(&runButton, 1);

		lcd.clear();
		lcd.putf("sd\nsd", "Rx: ", data,0, "Tx: ", runButton,0);
		lcd.disp();

		clock.wait(10);
	}
}
};
