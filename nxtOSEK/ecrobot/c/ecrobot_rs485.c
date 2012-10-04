/*****************************************************************************
 * FILE: ecrobot_rs485.c
 *
 * COPYRIGHT 2008-2010 Takashi Chikamasa <takashic@sourceforge.net> and Simone Casale Brunet
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

#include <stddef.h>
#include <string.h>

#include "ecrobot_base.h"
#include "ecrobot_private.h"
#include "ecrobot_interface.h"

typedef enum {
	RS485_DISABLED,
	RS485_ENABLED
} RS485_STATUS_T;

static volatile U8 rs485_status = RS485_DISABLED;

/*==============================================================================
 * NXT RS485 API
 *
 * RS485 default configrations:
 * LEGO default baud rate 921600 [bps] = DEFAULT_BAUD_RATE_RS485
 * Asynchronous mode
 * 8 bits character length
 * 1 stop bit
 * No parity check
 *=============================================================================*/
/**
 * Initialize RS485 and configure the sensor port 4 for RS485 communication.
 * @param baud_rate RS485 baud rate
 */
void ecrobot_init_rs485(U32 baud_rate)
{
	if (rs485_status == RS485_DISABLED)
	{
		hs_init();
		hs_enable(baud_rate);
		rs485_status = RS485_ENABLED;
	}
}

/**
 * Terminate RS485 (turn off the device and make the pins available for other uses).
 */
void ecrobot_term_rs485(void)
{
	hs_init(); // Turn off the device and make the pins available for other uses
	rs485_status = RS485_DISABLED;
}

/**
 * Send RS485 data.
 * @param off: buffer offset
 * @param len: length of the data to be sent
 * @return length of sent data
 */
U32 ecrobot_send_rs485(U8* buf, U32 off, U32 len)
{
	if (rs485_status == RS485_DISABLED) return 0;

	return hs_write(buf, off, len);
}

/**
 * Read RS485 data.
 *
 * @param buf: buffer for read data
 * @param off: buffer offset
 * @param len: length of data to be read
 * @return length of read data
 */
U32 ecrobot_read_rs485(U8* buf, U32 off, U32 len)
{
	if (rs485_status == RS485_DISABLED) return 0;

	return hs_read(buf, off, len);
}

