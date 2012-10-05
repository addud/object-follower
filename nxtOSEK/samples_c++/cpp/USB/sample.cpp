/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// This program needs to use nxtOSEK/samples_c/usbtest/usbhost/usbhost.exe.

#include <string.h>

// ECRobot++ API
#include "Usb.h"
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define DISCONNECT_REQ 0xFF

Usb usb;

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	usb.commHandler(); // USB communication handler
}


TASK(TaskMain)
{
	U32 len;
	U8 data[MAX_USB_DATA_LEN]; // first byte is preserved for disconnect request from host
	Lcd lcd;

	lcd.clear();
	lcd.putf("sn", "USB");
	lcd.putf("s", "Run usbhost.exe");
	lcd.disp();

	while(1)
  	{
  		if (usb.isConnected()) // check usb connection
  		{
			memset(data, 0, Usb::MAX_USB_DATA_LENGTH); // flush buffer
			len = usb.receive(data,0,Usb::MAX_USB_DATA_LENGTH); // receive data

  			if (len > 0)
  			{
  				if (data[0] == DISCONNECT_REQ)
  				{
  					usb.close(); // close usb connection
				}
				else
				{
					data[0] = 0x00;
					usb.send(data,0,len); // send data
				}
  			}
		}
  	}
}
}
