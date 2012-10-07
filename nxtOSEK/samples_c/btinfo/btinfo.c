/* btinfo.c for TOPPERS/ATK(OSEK) */
#include <stdio.h>

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


#define DEVICE_NAME "MYNXT" /* Bluetooth device name */
#define PASS_KEY    "1234"  /* Bluetooth pass key */

#define ADDRESS_STR "ADDRESS:"
#define DEVICE_STR  "DEVICE:"
#define RSSI_STR    "RSSI:"

static void send_bluetooth_info(U8* address, CHAR* dev_name, S16 rssi);
CHAR buf[BT_MAX_TX_BUF_SIZE];

void ecrobot_device_initialize()
{
	ecrobot_init_bt_slave(PASS_KEY);
}

void ecrobot_device_terminate()
{
	ecrobot_term_bt_connection();
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	U8 address[7];
	CHAR dev_name[16];
	S16 rssi;
	SINT i;

	/**
	 * Device name is set only when Bluetooth is NOT connected
	 */
	ecrobot_set_bt_device_name(DEVICE_NAME);

	display_clear(0);
	display_goto_xy(0, 0);
   	display_string("Getting info...");
   	display_update();
	/**
	 * Note that these Bluetooth API take several hundred seconds to retrieve
	 * the information. Hence it is not recommended to use the API in high speed
	 * periodical tasks
	 */
	ecrobot_get_bt_device_address(address);
	ecrobot_get_bt_device_name(dev_name);
	while(1)
	{
		rssi = ecrobot_get_bt_signal_strength();

		display_clear(0);

		display_goto_xy(0, 0);
	   	display_string(ADDRESS_STR);
		display_goto_xy(0, 1);
	   	for (i=0; i<7; i++)
	   	{
	   		display_hex(address[i],2);
	   	}

		display_goto_xy(0, 2);
	   	display_string(DEVICE_STR);
	   	display_string(dev_name);

		display_goto_xy(0, 3);
	   	display_string(RSSI_STR); /* Received Signal Strength Indicator */
	   	display_int(rssi, 0);

	   	display_update();

	   	if (rssi == -1)
	   	{
	   		/* Bluetooth is not connected */
			systick_wait_ms(500); /* 500msec wait */
	   	}
	   	else
	   	{
	   		/* Send information to PC terminal software.
	   		 * E.g. Tera Term (http://ttssh2.sourceforge.jp/index.html.en)
	   		 */
	   		send_bluetooth_info(address, dev_name, rssi);
	   	}
	}
}

/*
 * Note that sprintf is used to convert integer value to hex/decimal ASCII format,
 * but, of course, it's not good because of large memory consumption.
 */
static void send_bluetooth_info(U8* address, CHAR* dev_name, S16 rssi)
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

   	if (numOfBytes > BT_MAX_TX_BUF_SIZE)
   	{
   		numOfBytes = BT_MAX_TX_BUF_SIZE;
   	}
   	ecrobot_send_bt(buf, 0, numOfBytes);
}

