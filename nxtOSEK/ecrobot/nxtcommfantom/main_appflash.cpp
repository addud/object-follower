/**
 * Main program code of the appflash utility for Fantom.
 *
 * Copyright 2008 Takashi Chikamasa <takashic@cybernet.co.jp>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "nxtcommfantom.h"

#include "bios.h"
#include "flash_loader.h"


/*
 * calculate check sum of a data block
 *
 */
static unsigned int calc_check_sum(unsigned char* data, unsigned int len)
{
	unsigned int sum;

	sum = 0;
	for(int i = 0; i < len; i++)
	{
		sum += (unsigned int)data[i];
	}
	return sum;
}

int main(int argc, char *argv[])
{
	char *fw_file;
	FILE *f;
	char *buf;
	long lsize;

	ViChar nxt_id[MAX_DEV_ID];
	nFANTOM100_iNXT nxt;
	ViChar dev_name[MAX_DEV_NAME];
	char data[DATA_LENGTH];
	unsigned short data_num;

	printf("#=========================================================#\n");
	printf("#    Application Flash Utility with LEGO fantom driver    #\n");
	printf("#=========================================================#\n");

	/* check command format */
	if (argc != 2)
	{
		printf("SYNTAX: %s <Application program(*_rom.bin)>\n"
		"I.e. %s foo_app_rom.bin\n", argv[0], argv[0]);
		return 0;
	}

	/* read application file */
	fw_file = argv[1];
	f = fopen(fw_file, "rb");
	if (f == NULL)
	{
		printf("ERROR: opening file");
		return 0;
	}
	fseek(f, 0, SEEK_END);
	lsize=ftell(f);
	rewind(f);

	buf = (char *) malloc(lsize);
	if (buf == NULL)
	{
		printf("ERROR: allocating memory");
		fclose(f);
		return 0;
	}

	if (fread(buf, 1, lsize, f) != (int) lsize)
	{
		printf("ERROR: reading file");
		fclose(f);
		return 0;
	}
	fclose(f);

	/* check the required number of flash pages */
	data_num = (unsigned short)(lsize/DATA_LENGTH);
	if ((lsize % DATA_LENGTH) != 0) data_num++;
	if (data_num > MAX_NUM_FLASH_PAGES * 4)
	{
		printf("ERROR: file size is too large to upload.\n");
		return 0;
	}
	printf("%s: %ld [bytes]\n", fw_file, lsize);

	/* find a NXT */
	if (NXTCommFantom_find(nxt_id) == 0)
	{
		printf("ERROR: NXT not find.\n");
		printf("Is it properly plugged in via USB?\n");
		printf("Is NXT BIOS turned on?\n");
		return 0;
	}

	/* open the first found NXT */
	nxt = NXTCommFantom_open(nxt_id);
	if (nxt == NULL)
	{
		printf("ERROR: NXT found, but failed to open.\n");
		return 0;
	}

	/* check version of NXT BIOS */
	if(NXTCommFantom_getName(nxt, dev_name) == 0)
	{
		printf("ERROR: NXT found, but not return device name.\n");
		NXTCommFantom_close(nxt);
		return 0;
	}
	else if (strcmp((const char *)dev_name, VERSION) != 0)
	{
		printf("ERROR: appflash needs %s.\n", VERSION);
		NXTCommFantom_close(nxt);
		return 0;
	}

	/* check ECRobot USB API */
	if (NXTCommFantom_connect(nxt) == 0)
	{
		printf("ERROR: failed to connect with the NXT.\n");
		NXTCommFantom_close(nxt);
		return 0;
	}

	/* send number of 64 bytes block to be flashed */
	if (NXTCommFantom_send(nxt, (char *)&data_num, 0, 2) == 0)
	{
		printf("ERROR: failed to send data\n");
		printf("Keep pressing gray rectangle button on NXT longer than 1 second to turn off the NXT.\n");
		NXTCommFantom_close(nxt);
		return 0;
	}

	/* send application program every 64 bytes to NXT */
	for (int i = 0; i < lsize; i += DATA_LENGTH)
	{
		if (lsize - i >= DATA_LENGTH)
		{
			memcpy(data, &buf[i], DATA_LENGTH);
		}
		else
		{
			memset(data, 0, DATA_LENGTH);
			memcpy(data, &buf[i], lsize - i);
		}
		
		unsigned int sum = calc_check_sum((unsigned char*)data, DATA_LENGTH);
		if (NXTCommFantom_send(nxt, (char *)data, 0, DATA_LENGTH) == DATA_LENGTH)
		{
			int rx_len = 0;
			clock_t start = clock();
			while (rx_len == 0)
			{
				rx_len = NXTCommFantom_receive(nxt, (char *)data, 0, 4);

				if ((double)(clock() - start)/CLOCKS_PER_SEC > 5)
				{
					printf("ERROR: time out occurred.\n");
					printf("Keep pressing gray rectangle button on NXT longer than 1 second to turn off the NXT.\n");
					NXTCommFantom_close(nxt);
					return 0;
				}
			}

			if (rx_len != 4 || sum != *(unsigned int*)data)
			{
				/* check sum unmatched */
				printf("ERROR: failed to upload program.\n");
				printf("Keep pressing gray rectangle button on NXT longer than 1 second to turn off the NXT.\n");
				NXTCommFantom_close(nxt);
				return 0;
			}
		}
		else
		{
			printf("ERROR: failed to send data.\n");
			printf("Keep pressing gray rectangle button on NXT longer than 1 second to turn off the NXT.\n");
			NXTCommFantom_close(nxt);
			return 0;
		}
	}

	/* close the connection */
	NXTCommFantom_close(nxt);
	printf("Successful completion of uploading %s to the NXT.", fw_file);

	return 1;
}
