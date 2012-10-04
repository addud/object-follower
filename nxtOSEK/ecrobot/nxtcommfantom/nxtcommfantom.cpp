/**
 * ECRobot USB host interface for LEGO Fantom driver.
 *
 * Copyright 2008 Takashi Chikamasa <takashic@cybernet.co.jp>
 * based on jfantom.cpp by leJOS developers
 */
 
#include "fantom/iNXT.h"
#include "fantom/iNXTIterator.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "nxtcommfantom.h"

#define SYSTEM_COMMAND_REPLY	0x01
#define GET_FIRMWARE_VERSION	0x88
#define GET_DEVICE_INFO 		0x9B
#define USB_ECROBOT_MODE		0xff


/**
 * find a NXT in non-SAMBA mode.
 *
 * @param nxt_id: NXT id
 *
 * @return: 1(success)/0(failure)
 */
int NXTCommFantom_find(ViChar* nxt_id)
{
	nFANTOM100_iNXTIterator nxtIteratorPtr;
	ViStatus status = 0;

	// Create an NXT iterator object which is used to find all accessible NXT devices.
	
	// This does not work for multiple NXTs connected via USB(why?), so only one
	// NXT is expected to be connected
	nxtIteratorPtr = nFANTOM100_createNXTIterator(
		false /* don't search for NXTs over Bluetooth (only search USB) */,
		0 /* infinite timeout (ignored) */,
		&status );

	if (status >= VI_SUCCESS)
	{
		// get the name of the NXT
		nFANTOM100_iNXTIterator_getName(nxtIteratorPtr, nxt_id, &status);
		nFANTOM100_destroyNXTIterator(nxtIteratorPtr, &status);
		return 1;
	}
	return 0;
}

/**
 * open a USB port for the NXT
 * 
 * @param nxt_id: NXT id to be open
 * 
 * @return: handle of the NXT
 */
nFANTOM100_iNXT NXTCommFantom_open(ViChar* nxt_id)
{
	ViStatus status = 0;
	nFANTOM100_iNXT nxtPtr; 

	nxtPtr = nFANTOM100_createNXT(nxt_id, &status, false);
	if (status < VI_SUCCESS)
	{
    	return NULL;
	}
	return nxtPtr;
}

/**
 * get device name of the NXT
 *
 * @param nxt: handle of the NXT
 * @param name: device name of the NXT
 *
 * @return: 1(success)/0(failure)
 */
int NXTCommFantom_getName(nFANTOM100_iNXT nxt, ViChar* name)
{
	char buf[MAX_DATA_LEN];
	int read_len;
	int i;
	int timeout = 10000;

	/* get device info */
	buf[0] = (char)SYSTEM_COMMAND_REPLY;
	buf[1] = (char)GET_DEVICE_INFO;
	if(NXTCommFantom_send(nxt, buf, 0, 2) > 0)
	{
		while(timeout-- > 0)
		{
			read_len = NXTCommFantom_receive(nxt, buf, 0, 33);
			if (read_len > 0) break;
		}
		if (read_len == 0) return 0; /* no return until time out */

		/* return only device name */
        for (i = 0; i < 15 && buf[i + 3] != 0; i++)
        {
        	name[i] = (char)buf[i + 3];
        }
        name[i] = '\0';
	}
	return 1;
}

/**
 * connect with ECRobot USB API installed NXT.
 *
 * @param nxt: handle of the NXT
 *
 * @return: 1(success)/0(failure)
 */
int NXTCommFantom_connect(nFANTOM100_iNXT nxt)
{
	/* unique signature to connect with only ECRobot USB API */
	static const char ecrobot_sig[] = {'E', 'C', 'R', 'O', 'B', 'O', 'T'};
	char buf[MAX_DATA_LEN];
	int read_len;
	int i;
	int timeout = 10000;

	/* set packet mode */
	buf[0] = (char)SYSTEM_COMMAND_REPLY;
	buf[1] = (char)USB_ECROBOT_MODE;
	if(NXTCommFantom_send(nxt, buf, 0, 2) > 0)
	{
		while(timeout-- > 0)
		{
			read_len = NXTCommFantom_receive(nxt, buf, 0, MAX_DATA_LEN);
			if (read_len > 0) break;
		}
		if (read_len == 0) return 0; /* no return until time out */

		/* check the packet mode is set in the NXT */
        if ((read_len >= sizeof(ecrobot_sig)+1) && (buf[0] == (char)0x02))
        {
			for (i = 0; i < sizeof(ecrobot_sig); i++)
			{
				if (buf[i+1] != (char)ecrobot_sig[i]) return 0;
			}
			return 1;
		}
	}
	return 0;
}

/**
 * send USB packet data to the NXT
 *
 * @param nxt: handle of the NXT
 * @param data: data to send
 * @param offset: data offset
 * @param len: length of data to send
 *
 * @return: length of sent data
 */
int NXTCommFantom_send(nFANTOM100_iNXT nxt, char* data, int offset, int len)
{
	ViStatus status = 0;
	
	if (len > MAX_DATA_LEN) return 0;
	return nFANTOM100_iNXT_write(nxt,(const unsigned char *)data + offset, len, &status);
}

/**
 * receive USB packet data from the NXT
 *
 * @param nxt: handle of the NXT
 * @param data: data to receive
 * @param offset: data offset
 * @param len: length of data to receive
 *
 * @return: length of received data
 */
int NXTCommFantom_receive(nFANTOM100_iNXT nxt, char* data, int offset, int len)
{
	ViStatus status = 0;

	if (len > MAX_DATA_LEN) len = MAX_DATA_LEN;
	return nFANTOM100_iNXT_read(nxt, (unsigned char *)data + offset, len, &status);
}

/**
 * close the USB connection with the NXT
 * 
 * @param nxt: handle of the NXT
 * 
 */
void NXTCommFantom_close(nFANTOM100_iNXT nxt)
{
	ViStatus status = 0;
	
	if (nxt == NULL) return;
	nFANTOM100_destroyNXT(nxt, &status);
}

