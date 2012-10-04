/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "PSPNx.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

PSPNx psStick(PORT_1);

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Clock clock;
	Lcd lcd;

	while(1)
	{
		U8 rawData[PSPNx::DATA_BUFFER_BYTE_SIZE];

		//Mindsensor's support confirms that for certain gamepads, setting a mode
		//must be called several times until it becomes active
		psStick.setAnalog();
		psStick.update();

		psStick.get(rawData); // get raw I2C data
		//grab the first two bytes of the raw data (the button data)
	    U16 rawDigitalPad = *(reinterpret_cast<U16 const * const>(rawData));
	    //flip the bits
	    rawDigitalPad ^= 0xffff;

		lcd.clear();
	    //display the bit set indicating whether or not a digital button is pressed
	    for(int i = 0; i < 16; ++i)
	    {
	    	//quick and dirty way to display each bit's status
	    	lcd.putf("d", ((rawDigitalPad & (1 << i))? 1 : 0),0);
	    }

	    //display the analog stick data
	    lcd.cursor(0,1);
		lcd.putf("sddn", " LeftX/Y:", rawData[2],0, rawData[3],5);
		lcd.putf("sddn", "RightX/Y:", rawData[4],0, rawData[5],5);

		//example of how to read and use the three distinct digital button states
	    lcd.putf("s", "SQUARE:");
	    if(psStick.pressed(PSPNx::SQUARE))
	    {
	    	lcd.putf("s", "Pressed ");
	    }

	    if(psStick.held(PSPNx::SQUARE))
	    {
	    	lcd.putf("s", "Held    ");
	    }

	    if(psStick.released(PSPNx::SQUARE))
	    {
	    	lcd.putf("s", "Released");
	    }

	    lcd.disp();
	    clock.wait(20);
	}
}
}
