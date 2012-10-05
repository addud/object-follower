/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot++ API
#include "AccelSensor.h"
#include "CompassSensor.h"
#include "ColorSensor.h"
#include "IrSeeker.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

AccelSensor     accel(PORT_1);
CompassSensor compass(PORT_2);
ColorSensor     color(PORT_3);
IrSeeker           ir(PORT_4);

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;
	Lcd lcd;

	S16 axes[3]; // Accel Sensor data
	S16 heading; // Compass Sensor data
	S16 rgb[3];  // Color Sensor raw color data
	U8  num;     // Color Sensor data
	S16 dir;     // IR Seeker data
	
	// it may need to calibrate compass sensor
	compass.beginCalibration();
	bool calCompass = compass.endCalibration();

	while(1)
	{
		accel.getAccel(axes);
		heading = compass.getHeading();
		num = color.getColorNumber();
		color.getRawColor(rgb);
		dir = ir.getDirection();; 

		lcd.clear();
		lcd.putf("sn",   "HiTechnicSensors");
		lcd.putf("sddn", "X/Y: ", axes[0],0, axes[1],5); 
		lcd.putf("sdn",  "Z:   ", axes[2],0);
		lcd.putf("sddn", "C/Hd:", calCompass,0, heading,5);
		lcd.putf("sddn", "Nm/R:", num,0, rgb[0],5);
		lcd.putf("sddn", "G/B: ", rgb[1],0, rgb[2],5);
		lcd.putf("sd",   "Dir: ", dir,0);
		lcd.disp();

		clock.wait(100);
	}
}
}
