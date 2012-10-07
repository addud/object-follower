/* rs485test.c for TOPPERS/ATK(OSEK) */

#include <string.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


/*
 * Note that the sensor port 4 should be used for RS485 test
 */

#define DATA_LEN (8)

void ecrobot_device_initialize()
{
	ecrobot_init_rs485(DEFAULT_BAUD_RATE_RS485);
}

void ecrobot_device_terminate()
{
	ecrobot_term_rs485();
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

TASK(OSEK_Task_Background)
{
	U8 tx_data[DATA_LEN];
	U8 rx_data[DATA_LEN];
	U8 tx_cnt = 0;
	memset(tx_data, 0, DATA_LEN);
	memset(rx_data, 0, DATA_LEN);
	while(1)
	{
		U32 numOfRxData = ecrobot_read_rs485(rx_data, 0, DATA_LEN);
		if (numOfRxData > 0)
		{
			display_clear(0);
			for (U32 i=0; i<numOfRxData; i++)
			{
				display_goto_xy(0,i);
				display_int(rx_data[i], 0);
			}
			display_update();
		}

		if (ecrobot_is_ENTER_button_pressed())
		{
			for (U32 i=0; i<DATA_LEN; i++)
			{
				tx_data[i] = tx_cnt + i;
			}
			ecrobot_send_rs485(tx_data, 0, DATA_LEN);
			tx_cnt++;
		}

		systick_wait_ms(20); /* 20msec wait */
	}
}
