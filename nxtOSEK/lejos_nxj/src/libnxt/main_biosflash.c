/**
 * Main program code for the biosflash utility.
 *
 * Copyright 2006 David Anderson <david.anderson@calixo.net>
 * Modified 2007 by Lawrie Griffiths <lawrie.griffiths@ntlworld.com>
 * to flash nxj firmware and Java menu
 * Modified 2008 by Takashi Chikamasa <takashic@cybernet.co.jp> to
 * support NXT BIOS flashing
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
    nxt_close(nxt);
  exit(err);
}

int main(int argc, char *argv[])
{
  nxt_t *nxt;
  nxt_error_t err;
  char *bios_file;

  printf("#==========================================================#\n");
  printf("#                  NXT BIOS Flash Utility                  #\n");
  printf("#==========================================================#\n\n");

  if (argc == 1)
    {
      bios_file = (char *) calloc(1,256);
      strcat(bios_file,"../ecrobot/bios/nxt_bios_rom.bin");
    }
  else if (argc != 2)
    {
      printf("Syntax: %s [<NXT BIOS binary>]\n"
             "\n"
             "Example: %s nxt_bios_rom.bin\n", argv[0], argv[0]);
      exit(1);
    }
  else
    {
      bios_file = argv[1];     
    }

  printf("Checking NXT BIOS %s ... ", bios_file);
  NXT_HANDLE_ERR(nxt_firmware_validate(bios_file, MAX_BIOS_FLASH_PAGE ), NULL,
                 "Error in NXT BIOS file");
  printf("NXT BIOS OK.\n");

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

  if (!nxt_in_reset_mode(nxt))
    {
      printf("NXT found, but not running in reset mode.\n");
      printf("Please reset your NXT manually and restart this program.\n");
      exit(2);
    }

  NXT_HANDLE_ERR(nxt_open(nxt), NULL, "Error while connecting to NXT");

  printf("NXT device in reset mode located and opened.\n"
         "Starting NXT BIOS flash procedure now...\n");

  NXT_HANDLE_ERR(nxt_firmware_flash(nxt, bios_file, 0, MAX_BIOS_FLASH_PAGE, 1, 0), nxt,
                 "Error flashing NXT BIOS");
  printf("NXT BIOS flash complete.\n");

  NXT_HANDLE_ERR(nxt_jump(nxt, 0x00100000), nxt, "Error booting new NXT BIOS");
  printf("New NXT BIOS started!\n");

  NXT_HANDLE_ERR(nxt_close(nxt), NULL,
                 "Error while closing connection to NXT");
  return 0;
}
