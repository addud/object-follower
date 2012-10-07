/**
 * Main program code for the appflash utility.
 *
 * Copyright 2008 Takashi Chikamasa <takashic@cybernet.co.jp>
 * Based on runc by Lawrie Griffiths <lawrie.griffiths@ntlworld.com>
 * and fwflash by David Anderson <david.anderson@calixo.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "lowlevel.h"
#include "samba.h"
#include "firmware.h"

#include "flash_loader.h"

#define NXT_HANDLE_ERR(expr, nxt, msg)     \
  do {                                     \
    nxt_error_t nxt__err_temp = (expr);    \
    if (nxt__err_temp)                     \
      return handle_error(nxt, msg, nxt__err_temp);  \
  } while(0)

static int handle_error(nxt_t *nxt, char *msg, nxt_error_t err)
{
  printf("%s: %s\n", msg, nxt_str_error(err));
  if (nxt != NULL)
    /* nxt_close0 should be used for NXT BIOS(uses leJOS I/O driver) */
    nxt_close0(nxt);
  exit(err);
}

int main(int argc, char *argv[])
{
  nxt_t *nxt;
  nxt_error_t err;
  char *fw_file;
  FILE *f;
  int ret;
  char *buf;
  long lsize;

  unsigned char data[DATA_LENGTH];
  unsigned char echo_data[DATA_LENGTH];
  long i;
  unsigned short data_num;
  
  printf("#=========================================================#\n");
  printf("#                Application Flash Utility                #\n");
  printf("#=========================================================#\n\n");

  if (argc != 2)
  {
      printf("Syntax: %s <Application program image to write into Flash>\n"
             "\n"
             "Example: %s foo_app_rom.bin\n", argv[0], argv[0]);
      exit(1);
  }

  fw_file = argv[1];

  NXT_HANDLE_ERR(nxt_init(&nxt), NULL,
                 "Error during library initialization");

  err = nxt_find(nxt);
  if (err)
  {
      if (err == NXT_NOT_PRESENT)
        printf("NXT not found. Is it properly plugged in via USB?\n");
      else
        NXT_HANDLE_ERR(0, NULL, "Error while scanning for NXT");
      exit(1);
  }

  f = fopen(fw_file, "rb");
  if (f == NULL) NXT_HANDLE_ERR(8, NULL, "Error opening file");

  fseek(f, 0, SEEK_END);
  lsize=ftell(f);
  rewind(f);

  buf = (char *) malloc(lsize);
  if (buf == NULL) NXT_HANDLE_ERR(8, NULL, "Error allocating memory");

  ret = fread(buf, 1, lsize, f);

  if (ret != (int) lsize) NXT_HANDLE_ERR(8, NULL, "Error reading file");

  fclose(f);

  printf("File size is %ld bytes\n", lsize);

  /* check the required number of flash pages */
  data_num = (unsigned short)(lsize/DATA_LENGTH);
  if ((lsize % DATA_LENGTH) != 0) data_num++;
  if (data_num > MAX_NUM_FLASH_PAGES * 4)
  {
    printf("Error: File size is too large to upload.\n");
    return 0;
  }
  
  /* start accessing NXT */
  if (nxt_in_reset_mode(nxt))
  {
      printf("NXT found, but running in reset mode.\n");
      printf("Please turn on your NXT and run NXT BIOS.\n");
      exit(2);
  }
  /* nxt_open0 should be used for appflash */
  NXT_HANDLE_ERR(nxt_open0(nxt), NULL, "Error while connecting to NXT");
  printf("NXT device in reset mode located and opened.\n"
         "Uploading an application program to Flash...\n");

  /* send number of 64 bytes to be flashed */
  NXT_HANDLE_ERR(nxt_send_buf(nxt, (unsigned char *)&data_num, 2), NULL, "Error Sending data");

  /* send application program every 64 bytes to NXT */
  for (i = 0; i < lsize; i += DATA_LENGTH)
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

    NXT_HANDLE_ERR(nxt_send_buf(nxt, data, DATA_LENGTH), NULL, "Error Sending data");

	/* check sent data and echo-back data are same */
    NXT_HANDLE_ERR(nxt_recv_buf(nxt, echo_data, DATA_LENGTH), NULL, "Error Receiving data");
	if (memcmp(data, echo_data, DATA_LENGTH))
    {
      printf("Error: sent data is corrupted during program upload.\n");
      break;
	}
  }

  /* nxt_close0 should be used for appflash */
  NXT_HANDLE_ERR(nxt_close0(nxt), NULL,
                 "Error while closing connection to NXT");
  return 0;
}
