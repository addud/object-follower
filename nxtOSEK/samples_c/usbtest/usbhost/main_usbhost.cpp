/*
 * Main program code for USB host sample.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nxtcommfantom.h"
#include "usb_test.h"

int main(int argc, char *argv[])
{
	ViChar nxt_id[MAX_DEV_ID];
	nFANTOM100_iNXT nxt;
    ViChar name[MAX_DEV_NAME];
    char buf[MAX_DATA_LEN];

	/* find a NXT */
	if (NXTCommFantom_find(nxt_id) == 0)
	{
		printf("NXT not found.");
		return 0;
	}
	
	/* open the first found NXT */
	nxt = NXTCommFantom_open(nxt_id);
	if (nxt == NULL)
	{
		printf("NXT found, but failed to open.");
		return 0;
	}
	
	/* unique device name can be given to each NXT
	 * and it allows to communicate with multiple NXTs
	 */ 
//	if (NXTCommFantom_getName(nxt, name) == 1)
//	{
//		printf("NXT Device Name: %s\n", name);
//	}

	/* connect with ECRobot USB API */
	if (NXTCommFantom_connect(nxt) == 0)
	{
		printf("Failed to connect with the NXT.");
		NXTCommFantom_close(nxt);
		return 0;
	}
	
	/* now, this program could be connected with a NXT which uses
	 * ECRobot USB API
	 */

	printf("#========================================================#\n");
	printf("#           Simple USB host sample with Fantom           #\n");
	printf("#                                                        #\n");
	printf("# - Run usbtest program in the NXT before starting this  #\n");
	printf("#   program.                                             #\n");
	printf("# - Type characters and press Enter in the keyboard,     #\n");
	printf("#   NXT returns the same characters and displayed        #\n");
	printf("#   in the PC console.                                   #\n");
	printf("# - To stop this program, press Ctrl+Z (EOF).            #\n");
	printf("#========================================================#\n");

	/* echo back keyboard input */
	while((buf[1] = getchar()) != EOF)
	{
		buf[0] = 0x00;
		NXTCommFantom_send(nxt, buf, 0, 2);
		NXTCommFantom_receive(nxt, buf, 0, 2);
		putchar(buf[1]);
	}
	
	/* send disconnet request to the NXT */
	buf[0] = DISCONNECT_REQ;
	NXTCommFantom_send(nxt, buf, 0, 2);

	/* close the NXT */
	NXTCommFantom_close(nxt);

	return 0;
}
