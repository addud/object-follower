/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "SonarSensor.h"
#include "TouchSensor.h"
#include "Motor.h"
#include "Clock.h"
#include "Nxt.h"
#include "Lcd.h"
#include "Speaker.h"
#include "Bluetooth.h"
#include "Usb.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	// These device classes can be constructed as non global objects
	Clock clock;
	Nxt nxt;
	Lcd lcd;
	Speaker speaker;

	// The below device classes must be constructed as global objects.
	// Otherwise, an assertion will be displayed in the LCD
	// when the object is constructed.
	SonarSensor sonar(PORT_1); // I2c Assert
	TouchSensor touch(PORT_2); // Sensor Assert
	Motor       motor(PORT_A); // Motor Assert
	Bluetooth bt;              // Bt Assert
	Usb usb;                   // Usb Assert

	lcd.clear();
	lcd.putf("s", "No Device Assert");
	lcd.disp();  

	while(1);
}
}
