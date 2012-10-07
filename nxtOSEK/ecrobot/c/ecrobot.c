/*****************************************************************************
 * FILE: ecrobot.c
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

#include "ecrobot_base.h"
#include "ecrobot_private.h"
#include "ecrobot_interface.h"

#ifdef NXT_JSP
extern void lejos_osek_run(void);
#else
/* TOPPERS OSEK */
#include "kernel.h"
#include "cpu_insn.h"
#endif

/* If there was no operation on the NXT within SLEEP_TIME
 * after starting the system, turn the NXT into sleep (shut down)
 * to avoid battery discharge.
 */
#define SLEEP_TIME (1000*60*10) /* 10min */

SINT main(void)
{
#ifdef NO_RUN_ENTER_STOP_EXIT
	 
	init_OS_flag(); /* this should be called before device init */
	nxt_device_init();
	ecrobot_initDeviceStatus(); // added 10/28/2010 to fix a bug by tchikama
	ecrobot_init_nxtstate();

	if  (execution_mode() == EXECUTED_FROM_FLASH)
	{
		/*
		 * Call buttons_get() because ecrobot_get_button_state() has button bouncer.
		 * The button bouncer requires multiple periodical calls to make it work, but
		 * in this case, only single call (no while loop), so buttons_get is called. 
		 */
		if ((buttons_get() & 0x0F) == (ENTER_PRESSED | STOP_PRESSED))
		{
			/* set flash request and shut down the NXT
	 	 	 * at the next start, NXT BIOS will be executed.
	 	 	 */
			display_clear(0);
   			display_goto_xy(0, 0);
   			display_string("PWR ON: NXT BIOS");
			display_update();
			systick_wait_ms(1000);
   		
			set_flash_request();
			display_clear(1);
			systick_wait_ms(10);
			nxt_lcd_power_down(); /* reset LCD hardware */
			systick_wait_ms(10);
			while(1)
			{
				nxt_avr_power_down();
			}
		}
	}

	/* device init should be called prior to running the application */
	ecrobot_device_initialize();
	ecrobot_setDeviceInitialized();
	
	nxt_motor_set_count(NXT_PORT_A, 0);
	nxt_motor_set_count(NXT_PORT_B, 0);
	nxt_motor_set_count(NXT_PORT_C, 0);
	cpp_constructor();
	display_clear(1);
	systick_wait_ms(10);

#ifdef NXT_JSP
	interrupts_get_and_disable();
#else
	disable_int(); /* set_OS_flag and Start OS have to be atomic */
#endif
	set_OS_flag(); /* this shoud be called before starting OS */
#ifdef NXT_JSP
	lejos_osek_run(); /* start TOPPERS JSP */
#else
	StartOS(1);    /* start TOPPERS OSEK */
#endif

	/* never reached here */


#else
	/* 
	 * Default start up sequence
	 */
	U32 st;
	U32 last_act_time = 0;
	U32 flash_req_cnt = 0;

	init_OS_flag(); /* this should be called before device init */
	nxt_device_init();
	ecrobot_initDeviceStatus(); // added 10/28/2010 to fix a bug by tchikama
	ecrobot_init_nxtstate();

	show_splash_screen();
	show_main_screen();
	display_status_bar(1); /* clear status bar */
	add_status_info(execution_mode());
	display_status_bar(0); /* update status bar */
	while(1)
	{
		/* device init should be called prior to running the application */
		ecrobot_device_initialize();
		ecrobot_setDeviceInitialized();
		/* check the buttons every 10msec */
		st = systick_get_ms();
		if (st >= last_act_time + 10) 
		{
			last_act_time = st;
			ecrobot_poll_nxtstate();
			display_status_bar(0);

			/* 
			 * executed in FLASH: setup for the application flash
			 * executed in SRAM:  no effect
			 */
			if ((ecrobot_get_button_state() == (ENTER_PRESSED | STOP_PRESSED)) &&
			    (execution_mode() == EXECUTED_FROM_FLASH))
			{
				flash_req_cnt++;
				/* keep pusing ENTER + STOP buttons more than 1000msec */
				if (flash_req_cnt >= 100)
				{
					/* set flash request and shut down the NXT
				 	 * at the next start, NXT BIOS will be executed.
				 	 */
					ecrobot_device_terminate();
					set_flash_request();
					display_clear(1);
					systick_wait_ms(10);
					nxt_lcd_power_down(); /* reset LCD hardware */
					systick_wait_ms(10);
					while(1)
					{
						nxt_avr_power_down();
					}
				}
			}
			else
			{
				flash_req_cnt = 0;
				if ((ecrobot_get_button_state() == EXIT_PRESSED) || (systick_get_ms() > SLEEP_TIME))
				{
					/* shut down the NXT */
					ecrobot_device_terminate();
					display_clear(1);
					systick_wait_ms(10);
					nxt_lcd_power_down(); /* reset LCD hardware */
					systick_wait_ms(10);
					while(1)
					{
						nxt_avr_power_down();
					}
				}
				else if (ecrobot_get_button_state() == RUN_PRESSED)
				{
					nxt_motor_set_count(NXT_PORT_A, 0);
					nxt_motor_set_count(NXT_PORT_B, 0);
					nxt_motor_set_count(NXT_PORT_C, 0);
					cpp_constructor();
					display_clear(1);
					systick_wait_ms(10);
#ifdef NXT_JSP
					interrupts_get_and_disable();
#else
					disable_int(); /* set_OS_flag and Start OS have to be atomic */
#endif
					set_OS_flag(); /* this shoud be called before starting OS */
#ifdef NXT_JSP
					lejos_osek_run(); /* start TOPPERS JSP */
#else
					StartOS(1);    /* start TOPPERS OSEK */
#endif
					/* never reached here */
				}
			}
		}
    }
#endif    

    return 0;
}

