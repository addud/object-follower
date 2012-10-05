/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot++ API
#include "Clock.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Daq.h" // DAQ class for NXT GamePad
#include "Bluetooth.h"
#include "BTConnection.h"
using namespace ecrobot;


Lcd lcd;
Bluetooth bt;

static const CHAR* PASSKEY = "1234";

CHAR buf[Bluetooth::MAX_BT_RX_DATA_LENGTH];

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define MAX_NUM_OF_CHAR (16)
#define MAX_NUM_OF_LINE (8)

static void echoLcd(CHAR* data, int len);

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){}

TASK(TaskMain)
{
	Clock clock;
	Nxt nxt;
	BTConnection btConnection(bt, lcd, nxt);

	btConnection.connect(PASSKEY);
	lcd.clear(1);
	while(1)
	{
		U32 rx_len = bt.receive(buf, 0, Bluetooth::MAX_BT_RX_DATA_LENGTH);
		if (rx_len > 0)
		{
			echoLcd(buf, rx_len);
			bt.send(buf, 0, rx_len);
		}
	}
}

static void echoLcd(CHAR* data, int len)
{
	static int pos_x = 0;
	static int pos_y = 0;
	int i;

	/* set LCD postion in x, y */
	if (pos_x >= MAX_NUM_OF_CHAR)
	{
		pos_x = 0;
		pos_y++;
	}

	if (pos_y >= MAX_NUM_OF_LINE)
	{
		pos_x = 0;
		pos_y = 0;
	}

	if (pos_x == 0 && pos_y == 0)
	{
		lcd.clear();
	}
	lcd.cursor(pos_x, pos_y);

	for (i = 0; i < len; i++)
	{
		if (data[i] == '\n')
		{
			pos_x = 0;
			pos_y++;
			break;
		}
		else
		{
			lcd.putf("s", &data[i]);
			lcd.disp();
			if (i == (len - 1))
			{
				pos_x += len;
				break;
			}
		}
	}
}
}
