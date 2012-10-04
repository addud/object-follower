gcc -I./../../../../LibUSB-Win32/include -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -c error.c
gcc -I./../../../../LibUSB-Win32/include -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -c firmware.c
gcc -I./../../../../LibUSB-Win32/include -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -c flash.c
gcc -I./../../../../LibUSB-Win32/include -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -c lowlevel.c
gcc -I./../../../../LibUSB-Win32/include -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -c samba.c

ar r libnxt.a error.o firmware.o flash.o lowlevel.o samba.o

gcc -I./../../../../LibUSB-Win32/include -I./../../../ecrobot -I./../../../ecrobot/bios -I../nxtvm/platform/nxt -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -DLIBNXT -c main_biosflash.c
gcc -o ./../../../bin/biosflash.exe main_biosflash.o -L. -L./../../../../LibUSB-Win32/lib/gcc -lnxt -lusb

gcc -I./../../../../LibUSB-Win32/include -I./../../../ecrobot -I./../../../ecrobot/bios -I../nxtvm/platform/nxt -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -DLIBNXT -c main_appflash.c
gcc -o ./../../../bin/appflash.exe main_appflash.o -L. -L./../../../../LibUSB-Win32/lib/gcc -lnxt -lusb

gcc -I./../../../../LibUSB-Win32/include -I./../../../ecrobot -I./../../../ecrobot/bios -I../nxtvm/platform/nxt -Wall -std=gnu99 -D_NXT_LITTLE_ENDIAN -DLIBNXT -c main_ramboot.c
gcc -o ./../../../bin/ramboot.exe main_ramboot.o -L. -L./../../../../LibUSB-Win32/lib/gcc -lnxt -lusb

rm *.o

