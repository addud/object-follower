// Tribot RC sample.cpp for TOPPERS/ATK(OSEK)

#include <algorithm>

// ECRobot++ API
#include "Motor.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Clock.h"
#include "Speaker.h"
#include "GamePad.h"
#include "Bluetooth.h"
#include "BTConnection.h"
using namespace ecrobot;

#include "Driver.h"
#include "GamePadDriver.h"
#include "DriverManager.h"

//=============================================================================
// Device objects
Motor motorR(PORT_A, false); // brake:off
Motor motorL(PORT_B, false); // brake:off
Bluetooth bt;
Clock nxtClock;
Lcd lcd;
Nxt nxt;
Speaker speaker;

static const CHAR BT_PASS_KEY[] =  "1234"; // Bluetooth pass key

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
	// Establish blutooth connection with the PC
	BTConnection btConnection(bt, lcd, nxt);
	if (btConnection.connect(BT_PASS_KEY) == 1)
	{
		speaker.playTone(440U, 500U, 30U); // Beep a tone to inform the robot is ready to drive
	}

	// Define and register drivers
	GamePad gp(bt);
	GamePadDriver gpDriver(gp); // Control the robot using a PC HID gamepad controller
	Driver defaultDriver;
	DriverManager drivers;
	(void)drivers.createDriverTable(2);
	(void)drivers.add(&gpDriver); 	  // Highest priority
	(void)drivers.add(&defaultDriver); // Lowest priority

	VectorT<S16> cmd;
	while(1)
	{
		(void)drivers.update(); // This should be invoked prior to get the latest request
		switch(drivers.getRequest())
		{
			case Driver::DRIVE:
				cmd = drivers.getCommand();
				// Calculate PWM value for each motor based on the command received from the Gamepad
				S16 pwmR = cmd.mX - cmd.mY;
				S16 pwmL = cmd.mX + cmd.mY;
				// Check PWM limits
				pwmR = std::max(std::min(pwmR, static_cast<S16>(Motor::PWM_MAX)), static_cast<S16>(Motor::PWM_MIN));
				pwmL = std::max(std::min(pwmL, static_cast<S16>(Motor::PWM_MAX)), static_cast<S16>(Motor::PWM_MIN));
				motorR.setPWM(static_cast<S8>(pwmR));
				motorL.setPWM(static_cast<S8>(pwmL));
				break;
			default:
				break; // Do nothing
		}
		nxtClock.wait(40); // 40msec wait
	}
}
};

