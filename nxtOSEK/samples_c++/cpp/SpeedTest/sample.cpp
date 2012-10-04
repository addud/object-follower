//
// sample.cpp
//
// A sample program for Steve Hassenplug's speed benchmark test 
// (http://www.teamhassenplug.org/NXT/NXTSoftwareSpeedTest.html)
//

#include <stdlib.h> 

// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "Motor.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;


extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

LightSensor light(PORT_3);
SonarSensor sonar(PORT_4);
Motor       motorA(PORT_A);
Motor       motorB(PORT_B, false);
Motor       motorC(PORT_C, false);

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Lcd lcd;
	Clock nxtClock;
	int lightVal;
	int sonarVal;
	int rotateVal;
	int RN;
	int loop = 0;

	// Set A to 0
	int A = 0;

	// Start loop
	nxtClock.reset();
	while(1)
	{
		lcd.clear();

		// Read light sensor(3)
		lightVal = light.getBrightness();

		// Read US sensor(4)
		// Note that Sonar Sensor uses I2C to get data from the sensor
		// and acutually it is the bottle neck of this test.
		sonarVal = sonar.getDistance();

		// Read & Display Rotation Sensor(B)
		rotateVal = motorB.getCount();
		lcd.putf("sdn", "Rotation B:", rotateVal,0);

		// Get random number (1-100) (RN to be used later)
		RN = 1 + (int)(rand()*100.0/(1.0+RAND_MAX));

		// Display value of:(Light Sensor+US Sensor+Rotation Sensor)*100/(RN)
		lcd.putf("dn", (lightVal + sonarVal + rotateVal)*100/RN,0);

		// Set motor speed for B and C to RN (Using Coast)
		motorB.setPWM(RN);
		motorC.setPWM(RN);

		// If RN > 50, Increase A by 1
		// If RN < 50, Decrease A by 1
		// If RN = 50, no change to A
		if (RN > 50) A++;
		if (RN < 50) A--;

		// Display A
		lcd.putf("sdn", "A ", A,0);

		// Set motor A speed to A (if A<0, set direction to reverse)
		motorA.setPWM(A);

		// Display Loop Count
		lcd.putf("sd", "Loops: ", ++loop,0);

		// Loop for 60 seconds
		lcd.disp();
		if (nxtClock.now() >= 60*1000) break;
	}

	// Stop Motors
	motorA.reset();
	motorB.reset();
	motorC.reset();

	// Show display for 10 seconds
	nxtClock.wait(10*1000);
	lcd.clear(1);

	while(true);			 
}
}
