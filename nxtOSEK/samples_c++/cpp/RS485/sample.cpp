/* sample.cpp for TOPPERS/ATK(OSEK) */

#include <string>

// ECRobot++ API
#include "Clock.h"
#include "Lcd.h"
#include "Nxt.h"
#include "Rs485.h"
using namespace ecrobot;

/*
 * Note that the sensor port 4 should be used for RS485 test
 */
Clock nxtClock;
Rs485 rs485;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define DATA_LEN (8)

// nxtOSEK hook to be invoked from an ISR in category 2
void user_1ms_isr_type2(void)
{
	SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
	Lcd lcd;
	Nxt nxt;
	U8 tx_data[DATA_LEN];
	U8 rx_data[DATA_LEN];
	U8 tx_cnt = 0;
	memset(tx_data, 0, DATA_LEN);
	memset(rx_data, 0, DATA_LEN);
	while(1)
	{
		U32 numOfRxData = rs485.receive(rx_data, 0, DATA_LEN);
		if (numOfRxData > 0)
		{
			lcd.clear();
			for (U32 i=0; i<numOfRxData; i++)
			{
				lcd.putf("d\n", rx_data[i],0);
			}
			lcd.disp();
		}

		if (nxt.getButtons() == Nxt::ENTR_ON)
		{
			for (U32 i=0; i<DATA_LEN; i++)
			{
				tx_data[i] = tx_cnt + i;
			}
			rs485.send(tx_data, 0, DATA_LEN);
			tx_cnt++;
		}
		nxtClock.wait(20);
	}
}
}
