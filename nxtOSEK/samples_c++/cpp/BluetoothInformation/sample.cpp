/* sample.cpp for TOPPERS/ATK(OSEK) */

#include <stdio.h>

// ECRobot++ API
#include "Clock.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Bluetooth.h"
#include "BTConnection.h"
using namespace ecrobot;

Bluetooth bt;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define DEVICE_NAME "MYNXT" /* Bluetooth device name */
static const CHAR* PASSKEY = "1234";

#define ADDRESS_STR "ADDRESS:"
#define DEVICE_STR  "DEVICE:"
#define RSSI_STR    "RSSI:"

static void sendBluetoothInfo(U8* address, CHAR* dev_name, S16 rssi);
CHAR buf[Bluetooth::MAX_BT_TX_DATA_LENGTH];

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

TASK(TaskMain)
{
	Lcd lcd;
	Clock clock;
	Nxt nxt;

	BTConnection btc(bt, lcd, nxt);
	btc.connect(PASSKEY);

	bt.setFriendlyName(DEVICE_NAME); // name is changed only when Bluetooth is not connected

	lcd.clear();
	lcd.putf("s", "Getting info...");
	lcd.disp();

	U8 address[7];
	CHAR devName[16];
	bt.getDeviceAddress(address);
	bt.getFriendlyName(devName);

	lcd.clear();
	lcd.putf("s\n", ADDRESS_STR);
	for (int i=0; i<7; i++)
	{
		lcd.putf("x", address[i],2);
	}
	lcd.putf("\nss", DEVICE_STR, devName);

	while(1)
	{
		S16 rssi = bt.getRSSI();

		lcd.clearRow(3,0);
		lcd.cursor(0,3);
		lcd.putf("sd", RSSI_STR, rssi,0);
		lcd.disp();

		if (rssi == -1)
		{
			clock.wait(500);
		}
		else
		{
			sendBluetoothInfo(address, devName, rssi);
		}
	}
}

/*
 * Note that sprintf is used to convert integer value to hex/decimal ASCII format,
 * but, of course, it's not good because of large memory consumption.
 */
static void sendBluetoothInfo(U8* address, CHAR* dev_name, S16 rssi)
{
	SINT i;
	U32 numOfBytes = 0;

	/* set address */
	sprintf(&buf[numOfBytes], ADDRESS_STR);
	numOfBytes += sizeof(ADDRESS_STR);
   	for (i=0; i<7; i++)
   	{
   		if (address[i] < 16)
   		{
   			buf[numOfBytes + i*2] = '0';
   			sprintf(&buf[numOfBytes + i*2 + 1], "%x", address[i]);
   		}
   		else
   		{
   			sprintf(&buf[numOfBytes + i*2], "%x", address[i]);
   		}
   	}
   	numOfBytes += i*2;

   	/* set device name */
   	buf[numOfBytes++] = ' ';
	sprintf(&buf[numOfBytes], DEVICE_STR);
	numOfBytes += sizeof(DEVICE_STR);
   	for (i=0; i<16; i++)
   	{
   		if (dev_name[i] == '\0')
   		{
   			break;
   		}
		buf[numOfBytes++] = dev_name[i];
   	}

   	/* set RSSI */
   	buf[numOfBytes++] = ' ';
	sprintf(&buf[numOfBytes], RSSI_STR);
	numOfBytes += sizeof(RSSI_STR);
   	sprintf(&buf[numOfBytes], "%d\r\n", rssi);
   	if (rssi >= 100)
   	{
   		numOfBytes += 3;
   	}
   	else if (rssi >= 10)
   	{
   		numOfBytes += 2;
   	}
   	else
   	{
   		numOfBytes += 1;
   	}
   	numOfBytes += 2; /* CR + LF */

   	if (numOfBytes > Bluetooth::MAX_BT_TX_DATA_LENGTH)
   	{
   		numOfBytes = Bluetooth::MAX_BT_TX_DATA_LENGTH;
   	}
   	bt.send(buf, 0, numOfBytes);
}

}
