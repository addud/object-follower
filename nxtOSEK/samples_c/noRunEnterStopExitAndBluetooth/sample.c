/* btecho.c for TOPPERS/ATK(OSEK) */
#include <stdio.h>

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"


#define PASS_KEY    "1234"  /* Bluetooth pass key */

#define MAX_NUM_OF_CHAR (16)
#define MAX_NUM_OF_LINE (8)

static void echo_lcd(U8 *data, int len);
static void check_buttons(void);

CHAR buf[BT_MAX_RX_BUF_SIZE];

void ecrobot_device_initialize()
{
}

void ecrobot_device_terminate()
{
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }


TASK(OSEK_Task_Background)
{
	U32 rx_len;
	U8  bd_addr[7];

	display_clear(0);
	if (ecrobot_get_bt_device_address(bd_addr))
	{
		display_goto_xy(0, 0);
		display_string("BD_ADDR:");
		display_goto_xy(0, 1);
		for (int i = 0; i < 7; i++)
		{
			display_hex(bd_addr[i], 2);
		}
		display_goto_xy(3, 4);
		display_string("Waiting ...");
		display_goto_xy(0, 6);
	}
	display_string("Press any bttns");
	display_goto_xy(0, 7);
	display_string("to power off.");
	display_update();

	while(1)
	{
		/*
		 * Note that in case of NO_START_STOP_EXIT, Bluetooth initialization
		 * has to be invoked outside of ecrobot_device_initialize because
		 * the initialization is not invoked multiple times.
		 * So the Bluetooth initialization has be invoked multiple times in a loop like this.
		 */
		ecrobot_init_bt_slave(PASS_KEY);

		if (ecrobot_get_bt_status() == BT_STREAM)
		{
			// Connected and now Bluetooth stream is open.
			display_clear(1);
			break;
		}

		check_buttons();
	}

	while(1)
	{
		/* Echo back message from a PC terminal software.
   		 * E.g. Tera Term (http://ttssh2.sourceforge.jp/index.html.en)
   		 */
		rx_len = ecrobot_read_bt(buf, 0, BT_MAX_RX_BUF_SIZE);
		if (rx_len > 0)
		{
			echo_lcd((U8*)buf, rx_len);
			ecrobot_send_bt(buf, 0, rx_len);

			if (rx_len == 1)
			{
				if (buf[0] == 'r' || buf[0] == 'R')
				{
					ecrobot_term_bt_connection();
					// Restart NXT
					ecrobot_restart_NXT();
				}
				else if (buf[0] == 'q' || buf[0] == 'Q')
				{
					ecrobot_term_bt_connection();
					// Shutdown NXT
					ecrobot_shutdown_NXT();
				}
			}
		}

		check_buttons();
	}
}


static void check_buttons(void)
{
	// Press any buttons on the NXT shut downs the NXT
	if (ecrobot_get_button_state() && (BTN_RIGHT || BTN_LEFT || BTN_ORANGE_RECT || BTN_GRAY_RECT))
	{
		ecrobot_term_bt_connection();
		// Shutdown NXT
		ecrobot_shutdown_NXT();
	}
}


static void echo_lcd(U8 *data, int len)
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
