/*****************************************************************************
 * FILE: flash_loader.c
 *
 * COPYRIGHT 2008 Takashi Chikamasa <takashic@cybernet.co.jp>
 *
 * <About leJOS NXJ>
 *  leJOS NXJ is a full firmware replacement of LEGO Mindstorms NXT and 
 *  designed for Java programming environment for the NXT 
 *  ( For more detailed information, please see: http://lejos.sourceforge.net/ )
 *  In the leJOS NXJ distribution, C source files for NXT platform layer is also
 *  included besides with the Java VM. The platform C source code is well
 *  structured, comprehensive, and achieved higher performance than the LEGO's
 *  one. Therefore, leJOS NXJ (platform) is also the best GCC based C/C++  
 *  development platform for NXT.
 *
 *  The contents of this file are subject to the Mozilla Public License
 *  Version 1.0 (the "License"); you may not use this file except in
 *  compliance with the License. You may obtain a copy of the License at
 *  http://www.mozilla.org/MPL/
 *
 *  Software distributed under the License is distributed on an "AS IS"
 *  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *  License for the specific language governing rights and limitations
 *  under the License.
 *
 *  The Original Code is TinyVM code, first released March 6, 2000,
 *  later released as leJOS on September 23, 2000.
 *
 *  The Initial Developer of the Original Code is Jose H. Solorzano.
 *
 *  Contributor(s): see leJOS NXJ ACKNOWLEDGEMENTS .
 *
 *
 * <About TOPPERS OSEK>
 *  TOPPERS OSEK is an open source OSEK kernel and developed by TOPPERS project.
 *  TOPPERS(Toyohashi OPen Platform for Embedded Real-time Systems) has been managed 
 *  by a Non Profit Organization founded in Sep. 2003 and has been led by Professor
 *  Hiroaki Takada of Nagoya University in Japan. 
 *
 *  TOPPERS OSEK program is covered by the TOPPERS License as published
 *  by the TOPPERS PROJECT (http://www.toppers.jp/en/index.html).
 *
 *****************************************************************************/

#include <string.h>

/* leJOS NXJ I/O driver */
#include "mytypes.h"
#include "interrupts.h"
#include "aic.h"
#include "AT91SAM7.h"
#include "uart.h"
#include "systick.h"
#include "nxt_avr.h"
#include "twi.h"
#include "platform_hooks.h"
#include "nxt_avr.h"
#include "nxt_lcd.h"
#include "nxt_motors.h"
#include "sensors.h"
#include "display.h"
#include "i2c.h"
#include "bt.h"
#include "sound.h"
#include "udp.h"

#include "flash_loader.h"
#include "bios_display.h"
#include "bios.h"

#include "ecrobot_usb.h"

/*
 * verify flash pages
 *
 * return:
 *	1: data is flashed correctly
 *	0: data mismatch occurred
 */
static int verify_flash_page(int start_page, U8 *data, int page_num)
{
	int i;
	volatile U8 *page_addr;

	page_addr = (volatile U8 *)(FLASH_START_ADDR + 
		(start_page + page_num) * FLASH_PAGE_SIZE);

	for (i = 0; i < FLASH_PAGE_SIZE; i++)
	{
		if (data[i] != page_addr[i])
		{
			return 0;
		}
	}
	return 1;
}

/*
 * set BIOS version to record
 *
 * return:
 *  1: succeed to set BIOS version
 *  0: failed to set BIOS version
 */
static int set_bios_version(void)
{
	U8 data[FLASH_PAGE_SIZE];

	memset(data, 0, FLASH_PAGE_SIZE);
	strcpy((char *)data, VERSION);
	flash_write_page(FLASH_RECORD_START_PAGE, (U32 *)data, 0);
	return (verify_flash_page(FLASH_RECORD_START_PAGE, data, 0));
}

/*
 * calculate check sum of a data block
 *
 */
static U32 calc_check_sum(U8* data, U32 len)
{
	U32 sum;

	sum = 0;
	for(int i = 0; i < len; i++)
	{
		sum += (U32)data[i];
	}
	return sum;
}

/*
 * check BIOS version record to judge the new version is
 * same as remaining version record.
 *
 * return:
 *	1: version is same
 *	0: version is different
 */
int is_bios_version_equal(void)
{
	char *version;

	version = (char *)(FLASH_START_ADDR + FLASH_RECORD_START_PAGE * FLASH_PAGE_SIZE);
	return ((int)!strcmp((const char *)version, VERSION));
}

/*
 * check whether a flash request was set or not.
 *
 * return:
 *  1: flash is requested
 *  0: flash is not requested
 */
int has_flash_request(void)
{
	char *request;

	request = (char *)(FLASH_START_ADDR + FLASH_REQUEST_START_PAGE * FLASH_PAGE_SIZE);
	return ((int)!strcmp((const char *)request, FLASH_REQUEST));
}

/*
 * set a flash request to record
 *
 * return:
 *  1: succeeded to set a flash request
 *  0: failed to set a flash request
 */
int set_flash_request(void)
{
	U8 data[FLASH_PAGE_SIZE];

	memset(data, 0, FLASH_PAGE_SIZE);
	strcpy((char *)data, FLASH_REQUEST);
	flash_write_page(FLASH_REQUEST_START_PAGE, (U32 *)data, 0);
	return (verify_flash_page(FLASH_REQUEST_START_PAGE, data, 0));
}

/*
 * zero clear a flash request in record
 *
 * return:
 *  1: succeeded to clear a flash request
 *  0: failed to clear a flash request
 */
int clear_flash_request(void)
{
	U8 data[FLASH_PAGE_SIZE];

	memset(data, 0, FLASH_PAGE_SIZE);
	flash_write_page(FLASH_REQUEST_START_PAGE, (U32 *)data, 0);
	return (verify_flash_page(FLASH_REQUEST_START_PAGE, data, 0));
}

/*
 * flash loader to upload an application
 */
int flash_loader(void)
{
	#define EXIT_BUTTON 0x08
	#define EXIT_CNT_LIMIT 1000 /* msec */

	U8 data[FLASH_PAGE_SIZE];
	U8 appflash_status;
	volatile int len;
	volatile int data_offset;
	volatile int received_data_blocks;
	volatile int total_data_blocks;
	volatile int flash_page_num;
	U32 exit_cnt;

	display_bios_status(UPLOAD_IDLE, 0);

	ecrobot_init_usb();
	ecrobot_set_name_usb((U8 *)VERSION); /* this will be checked in appflash */

	exit_cnt = 0;
	total_data_blocks = -1;
	appflash_status = ON_PROGRESS;
	while(1)
	{
		ecrobot_process1ms_usb();
		systick_wait_ms(1);

		len = ecrobot_read_usb(&data[data_offset], 0, DATA_LENGTH); /* receive a 64bytes data block */

        /*
         * The flash sequence is performed as the following way:
         * 1. If two bytes data was received, it contains total number of 64bytes data blocks to be flashed.
         * 2. AT91SAM7S flash controller performs every 256 bytes (called a page), so the flash loader accumurates recived data until
         * received data reached to 256bytes (= a flash page) or reached to the last data block to be received.
         */
		if (total_data_blocks == -1 && len == 2 && appflash_status == ON_PROGRESS)
		{
			/* get total number of 64bytes data blocks to be received and initialize flash loader */
			total_data_blocks = *((unsigned short *)&data[0]);
			memset(data, 0, FLASH_PAGE_SIZE); /* clear the buffer */
			received_data_blocks = 0;
			data_offset = 0;
			flash_page_num = 0;
			display_bios_status(1, 0); /* upload begins */
			continue;
		}
		
		
		if (total_data_blocks != -1 && len == DATA_LENGTH && appflash_status == ON_PROGRESS) /* perform application flash */
		{
			/* send back check sum of received data block */
			U32 sum = calc_check_sum(&data[data_offset], DATA_LENGTH);
			ecrobot_send_usb((U8*)&sum, 0, 4); 
			systick_wait_ms(1);

			/* accumurate received data until reaching to flash page size */
			data_offset += DATA_LENGTH;
            received_data_blocks++;
			if (data_offset >= FLASH_PAGE_SIZE)
			{
				/* accumurated data blocks reached to 256bytes */
				flash_write_page(FLASH_START_PAGE, (U32 *)data, flash_page_num); /* flash one page */
				if (verify_flash_page(FLASH_START_PAGE, data, flash_page_num))
				{
					memset(data, 0, FLASH_PAGE_SIZE); /* clear the data buffer */
					data_offset = 0;
					flash_page_num++;
				}
				else
				{
					/* failed to flash, so cancel flash procedure */
					appflash_status = FAILED;
					total_data_blocks = -1;
					display_bios_status(UPLOAD_FAILED, 0);
				}
			}

			if (appflash_status == ON_PROGRESS && received_data_blocks >= total_data_blocks)
			{
				/* received data blocks reached to the last data blocks to be received */
				
				if (total_data_blocks % (FLASH_PAGE_SIZE/DATA_LENGTH))
				{
					/* if there was reminded data to be flashed, it would require one additional flash page */
					flash_write_page(FLASH_START_PAGE, (U32 *)data, flash_page_num);
					if (!verify_flash_page(FLASH_START_PAGE, data, flash_page_num))
					{
						/* failed to flash, so cancel flash procedure */
						appflash_status = FAILED;
						display_bios_status(UPLOAD_FAILED, 0);
					}
				}
				
				if (appflash_status == ON_PROGRESS)
				{
					if (!set_bios_version())
					{
						appflash_status = FAILED;
						display_bios_status(UPLOAD_FAILED, 0);
					}
					else
					{
						/* flash was finally succeeded */
						display_bios_status(UPLOAD_FINISHED, 0);
						
						/* execute uploaded application */ 
						exec_app();
					}
				}
				total_data_blocks = -1; /* terminate flash procedure */
			}
		}

		if (buttons_get() == EXIT_BUTTON)
		{
			if (++exit_cnt >= EXIT_CNT_LIMIT || total_data_blocks == -1)
			{
				if (appflash_status == ON_PROGRESS && total_data_blocks == -1)
				{
					terminate_flash(); /* turn off the NXT */
				}
				return 0; /* flash procedure was failed */
			}
		}
		else
		{
			exit_cnt = 0;
		}
	}
	return 1; /* never reached here */
}

void terminate_flash(void)
{
	ecrobot_term_usb();
	display_clear(1);
	systick_wait_ms(10);
	nxt_lcd_power_down(); /* reset LCD hardware */
	systick_wait_ms(20);
	
	while(1)
	{
		nxt_avr_power_down();
	}
}

void exec_app(void)
{
	ecrobot_term_usb();
	display_clear(1);
	systick_wait_ms(10);
	nxt_lcd_power_down(); /* reset LCD hardware */
	systick_wait_ms(20);
	
	JUMP_TO_APPLICATION
}


void nxt_device_init(void)
{
	aic_initialise();
	interrupts_enable();
	nxt_avr_init();
	systick_init();
	i2c_init();
	nxt_motor_init();
	sound_init();
	bt_init();
	systick_wait_ms(1000); /* wait for LCD to stabilize */
	display_init();
	init_sensors();
}


