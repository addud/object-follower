//
// BTConnection.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "BTConnection.h"
using namespace ecrobot;

//=============================================================================
// Establish Bluetooth connection as a slave device and display the status in the LCD.
SINT BTConnection::connect(const CHAR* passkey, const CHAR* devname)
{
	CHAR  name[16];
	U8 address[7];
	SINT ret = -1;

	mrLcd.clear();
	if (mrBt.getDeviceAddress(address)) // get the device address
	{
		if (devname != 0)
		{
			mrBt.setFriendlyName(devname); // set the friendly device name
		}
		mrBt.getFriendlyName(name); // display the friendly device name
		mrLcd.putf("ss", "NAME: ", name);
		mrLcd.cursor(0,1);
		mrLcd.putf("s", "BD_ADDR:");
		mrLcd.cursor(0,2);
		for (SINT i=0; i<7; i++)
		{
			mrLcd.putf("x", address[i],2);
		}
		mrLcd.cursor(0,5);
		mrLcd.putf("s", "================");
		mrLcd.cursor(0,6);
		mrLcd.putf("s", "<STP CANCEL    >");
		mrLcd.cursor(0,7);
		mrLcd.putf("s", "      EXIT      ");
		mrLcd.disp();

		while(1)
		{
			// connect as a slave device
			if (mrBt.waitForConnection(passkey, 500)) // wait for 500msec
			{
				mrLcd.cursor(0,4);
				mrLcd.putf("s", "[BT]");
				mrLcd.cursor(0,6);
				mrLcd.putf("s", "<STP           >");
				ret = 1;
				break;
			}
			else
			{
				if (mrNxt.getButtons() & Nxt::ENTR_ON) // connection was canceled
				{
					mrBt.cancelWaitForConnection(); // Cancel Bluetooth connection process
					mrLcd.clear();
					ret = 0;
					break;
				}
			}
		}
	}
	else
	{
		mrLcd.putf("s\ns\ns", "BT FAILED.", "TURN OFF THE NXT", "AND RESTART IT.");
	}
	mrLcd.disp();
	return ret;
}

//=============================================================================
// Establish Bluetooth connection as a master device and display the status in the LCD.
SINT BTConnection::connect(const CHAR* passkey, const U8 address[7])
{
	U8 dummy[7];
	SINT ret = -1;

	mrLcd.clear();
	if (mrBt.getDeviceAddress(dummy)) // get the device address to confirm the BlueCore active
	{
		mrLcd.putf("s", "BT MASTER TO");
		mrLcd.cursor(0,1);
		mrLcd.putf("s", "BD_ADDR:");
		mrLcd.cursor(0,2);
		for (SINT i=0; i<7; i++)
		{
			mrLcd.putf("x", address[i],2);
		}
		mrLcd.cursor(0,5);
		mrLcd.putf("s", "================");
		mrLcd.cursor(0,6);
		mrLcd.putf("s", "<STP CANCEL    >");
		mrLcd.cursor(0,7);
		mrLcd.putf("s", "      EXIT      ");
		mrLcd.disp();

		while(1)
		{
			// connect as a master device
			if (mrBt.waitForConnection(passkey, address, 500)) // wait for 500msec
			{
				mrLcd.cursor(0,4);
				mrLcd.putf("s", "[BT]");
				mrLcd.cursor(0,6);
				mrLcd.putf("s", "<STP           >");
				ret = 1;
				break;
			}
			else
			{
				if (mrNxt.getButtons() & Nxt::ENTR_ON) // connection was canceled
				{
					mrBt.cancelWaitForConnection(); // Cancel Bluetooth connection process
					mrLcd.clear();
					ret = 0;
					break;
				}
			}
		}
	}
	else
	{
		mrLcd.putf("s\ns\ns", "BT FAILED.", "TURN OFF THE NXT", "AND RESTART IT.");
	}
	mrLcd.disp();
	return ret;
}

