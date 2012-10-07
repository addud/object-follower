/* usbtest.c */
#include <string.h>

#include "kernel.h"
#include "kernel_id.h"

#include "ecrobot_interface.h"
#include "usb_test.h"

/* OSEK declarations */
DeclareTask(Task_ts1);
DeclareTask(Task_background);
DeclareResource(USB_Rx);
DeclareCounter(SysTimerCnt);

#define MAX_NUM_OF_CHAR 16
#define MAX_NUM_OF_LINE 8

static int pos_x = 0;
static int pos_y = 0;

static void showInitScreen(void)
{
	pos_x = 0;
	pos_y = 0;

	display_clear(0);
	display_goto_xy(0, 0);
	display_string("USB TEST");
	display_goto_xy(0, 1);
	display_string("Run usbhost.exe");
	display_update();	
}

static void display_usb_data(U8 *data, int len)
{
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
		display_clear(0);
	}
	display_goto_xy(pos_x, pos_y);

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
			display_string((char *)&data[i]);
			display_update();
			if (i == (len - 1))
			{
				pos_x += len;
				break;
			}
		}
	}
}

/* ECRobot hooks */
void ecrobot_device_initialize()
{
	ecrobot_init_usb(); /* init USB */
}

void ecrobot_device_terminate()
{
	ecrobot_term_usb(); /* terminate USB */
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
	/* Increment System Timer Count to activate periodical Tasks */
	(void)SignalCounter(SysTimerCnt);
}

/* 1msec periodical Task */
TASK(Task_ts1)
{
	GetResource(USB_Rx);
	ecrobot_process1ms_usb(); /* USB process handler (must be invoked every 1msec) */
	ReleaseResource(USB_Rx);

	TerminateTask();
}

/* background Task */
TASK(Task_background)
{
	int len;
	U8 data[MAX_USB_DATA_LEN]; /* first byte is preserved for disconnect request from host */

	showInitScreen();

	while(1)
  	{
		memset(data, 0, MAX_USB_DATA_LEN); /* flush buffer */
		/* critical section */
		GetResource(USB_Rx);
		len = ecrobot_read_usb(data, 0, MAX_USB_DATA_LEN); /* read USB data */
		ReleaseResource(USB_Rx);

  		if (len > 0)
  		{
  			if (data[0] == DISCONNECT_REQ)
  			{
  				/* disconnect current connection */
				ecrobot_disconnect_usb();
				showInitScreen();
			}
			else
			{
				data[0] = 0x00;
				ecrobot_send_usb(data, 0, len); /* send back received USB data */
				display_usb_data(&data[1], len-1);
			}
  		}
	}
}
