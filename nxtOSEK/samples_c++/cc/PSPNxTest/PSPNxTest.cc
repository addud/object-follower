//
// PSPNxTest.cc
//
// Testing module for the Mindsensor PSPNx wrapper class
//
// 09.28.2008 Jon C. Martin


#include "PSPNx.h"
//
// To properly interface with LEJOS-OSEK, we need to use C linkage between our
// code and LEJOS-OSEK
//

#define PSPNx_DEFAULT_PORT 0x02
extern "C" {

#include "ecrobot_interface.h"

  DeclareTask(Task1);
  
  TASK(Task1) {
	PSPNx psStick(NXT_PORT_S1, PSPNx_DEFAULT_PORT);
	display_clear(0);

	while(1)
	{
		//Mindsensor's support confirms that for certain gamepads, setting a mode
		//must be called several times until it becomes active
		psStick.setAnalog();
		psStick.update();

	    U8 const * const rawData = psStick.getRawData();
	    
	    //grab the first two bytes of the raw data (the button data)
	    U16 rawDigitalPad = *(reinterpret_cast<U16 const * const>(rawData));
	    //flip the bits 
	    rawDigitalPad ^= 0xffff;
	    
	    //display the bit set indicating whether or not a digital button is pressed
	    for(int i = 0; i < 16; ++i)
	    {
	    	display_goto_xy(i,0);
	    	//quick and dirty way to display each bit's status
	    	display_int((rawDigitalPad & (1 << i))? 1 : 0, 0);
	    }
	    
	    //display the analog stick data
	    display_goto_xy(0,1);
	    display_int(rawData[2], 0);
	    display_goto_xy(4,1);
	    display_int(rawData[3], 0);
	    display_goto_xy(0,2);
	    display_int(rawData[4], 0);
	    display_goto_xy(4,2);
	    display_int(rawData[5], 0);
	    
		//example of how to read and use the three distinct digital button states
	    if(psStick.pressed(PSPNx_SQUARE))
	    {
	    	display_clear(0);
	    	display_goto_xy(0,4);
	    	display_string("Pressed");
	    }
	    
	    if(psStick.held(PSPNx_SQUARE))
	    {
	    	display_goto_xy(0,5);
	    	display_string("Held");
	    }
	    
	    if(psStick.released(PSPNx_SQUARE))
	    {
	    	display_goto_xy(0,6);
	    	display_string("Released");
	    }
	    
		//press select to clear the display
	    if(psStick.pressed(PSPNx_SELECT))
	    {
	    	display_clear(0);
	    }
	    
	    display_update();
	}
  }
};
