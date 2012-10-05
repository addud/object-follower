// NXTway-GS++ sample.cpp for TOPPERS/ATK(OSEK)
//
// The robot building instructions are available at nxtOSEK website.
// See http://lejos-osek.sourceforge.net/NXTway-GS_Building_Instructions.pdf

// ECRobot++ API
#include "TouchSensor.h"
#include "SonarSensor.h"
#include "LightSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "Nxt.h"
#include "Clock.h"
#include "Lcd.h"
#include "GamePad.h"
#include "Daq.h"
#include "Speaker.h"
#include "Bluetooth.h"
#include "BTConnection.h"
using namespace ecrobot;

#include "NXTway_GS.h"
#include "Driver.h"
#include "StartStopDriver.h"
#include "SonarDriver.h"
#include "GamePadDriver.h"
#include "DriverManager.h"

//=============================================================================
// Device objects
TouchSensor touch(PORT_1); // Touch Sensor is used to start/stop the robot
SonarSensor sonar(PORT_2);
//LightSensor light(PORT_3); // Not used for NXTway-GS
GyroSensor   gyro(PORT_4);
Motor      motorR(PORT_B);
Motor      motorL(PORT_C);
Bluetooth bt;
Clock clock;
Nxt nxt;
Lcd lcd;
Speaker speaker;

SonarDriver sonarDriver; // called from multiple Tasks

static const CHAR BT_PASS_KEY[] =  "1234"; // Bluetooth pass key

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

//=============================================================================
// TOPPERS/ATK declarations
DeclareCounter(SysTimerCnt);
DeclareAlarm(Alarm4msec);
DeclareEvent(EventDrive);

//=============================================================================
// 1msec timer interrupt hook
void user_1ms_isr_type2(void)
{
	(void)SignalCounter(SysTimerCnt); // Alarm counter
	SleeperMonitor(); // Need for Nxt and I2C device classes
}

//=============================================================================
// Main Task
TASK(TaskMain)
{
	// establish blutooth connection with a PC to use a PC HID GamePad controller
	BTConnection btConnection(bt, lcd, nxt);
	(void)btConnection.connect(BT_PASS_KEY);

	for (U32 i = 5; i <= Lcd::MAX_CURSOR_Y; i++) lcd.clearRow(i);
	lcd.cursor(0,5);
	lcd.putf("snsns", "TOUCH:START/STOP", "STAND IT UP AND", "WAIT FOR A BEEP.");
	lcd.disp();
	SetRelAlarm(Alarm4msec, 1, 4); // Set 4msec periodical Alarm for the drive event

	while(1)
	{
		sonarDriver.checkObstacles(sonar);
		clock.wait(40); // 40msec wait
	}
}

//=============================================================================
// Drive Task
TASK(TaskDrive)
{
	Daq daq(bt);
	GamePad gp(bt);

	// Define and register drivers
	StartStopDriver ssDriver(touch);
	GamePadDriver gpDriver(gp);
	Driver balancingDriver;
	DriverManager drivers;
	(void)drivers.createDriverTable(4);
	(void)drivers.add(&ssDriver);        // Highest priority
	(void)drivers.add(&sonarDriver);
	(void)drivers.add(&gpDriver);
	(void)drivers.add(&balancingDriver); // Lowest priority

	NXTway_GS robot(nxt, gyro, motorL, motorR);

	while(1)
	{
		(void)drivers.update(); // This should be invoked prior to get the latest request
		switch(drivers.getRequest())
		{
			case Driver::STOP:
				robot.stop();
				break;
			case Driver::START:
				CancelAlarm(Alarm4msec);            // Cancel the alarm request to stop calling this task periodically
				robot.reset(robot.calGyroOffset()); // Reset the robot with dynamic calibration and it takes 400msec
				speaker.playTone(440U, 500U, 30U);  // Beep a tone to inform the robot is ready to drive
				SetRelAlarm(Alarm4msec, 1, 4);      // Resume the alarm request
				break;
			case Driver::DRIVE:
				robot.drive(drivers.getCommand());
				// DAQ by NXT GamePad
				S8 cmdFrame[2];
				cmdFrame[0] = static_cast<S8>(drivers.getCommand().mX);
				cmdFrame[1] = static_cast<S8>(drivers.getCommand().mY);
				daq.send(cmdFrame, static_cast<S32>(drivers.getById()));
				break;
			default:
				break; // Do nothing
		}
		WaitEvent(EventDrive);  // Wait for drive event
        ClearEvent(EventDrive); // Clear the drive event
	}
}
};

