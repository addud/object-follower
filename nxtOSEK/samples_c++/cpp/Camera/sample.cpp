/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "Camera.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Camera camera(PORT_1);

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;
	Lcd lcd;

	camera.sortBy(Camera::SIZE); // SIZE/COLOR/NO_SORTING
	camera.enableTracking(true); // start tracking

	while(1)
	{
		camera.update(); // receive all data from the camera

		lcd.clear();
		int numOfObjects = camera.getNumberOfObjects(); // get number of objects being tracked
		if (numOfObjects >= 1 && numOfObjects <= 8)
		{
			Camera::Rectangle_T rect;
			for (int i = 0; i < numOfObjects; i++)
			{
				SINT objectColor = camera.getObjectColor(i); // get object color
				camera.getRectangle(i, &rect); // get rectangle data(upper left X/Y, lower right X/Y, width and height)
				lcd.putf("sdsdddn", "Obj", i+1,0, " ", objectColor,0, rect.width,4, rect.height,4);
			}
		}
		else
		{
			lcd.putf("s", "NO OBJECTS");
		}

		lcd.disp();
	    clock.wait(50);
	}
}
}
