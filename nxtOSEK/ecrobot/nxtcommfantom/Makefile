CC = gcc -m32 -march=i386
FANTOM = /Users/Dmitry/Downloads/nxtpp-0.5
OSEK = /Users/Dmitry/CPP/nxtOSEK
DEPLOY = $(OSEK)/bin

INC_BIOS = $(OSEK)/ecrobot/bios
INC_NXT = $(OSEK)/lejos_nxj/src/nxtvm/platform/nxt
INC_FANTOM = $(FANTOM)/include

OSEK_ROOT = $(ROOT)/toppers_jsp

all: appflash

appflash:	main_appflash.o nxtcommfantom.o
	$(CC) \
	-framework Fantom \
	main_appflash.o nxtcommfantom.o \
	-o $(DEPLOY)/appflash
	rm -f *.o

main_appflash.o:	main_appflash.cpp
	$(CC) \
	-c \
	-I. -I$(INC_BIOS) -I$(INC_NXT) -I$(INC_FANTOM) \
	main_appflash.cpp

nxtcommfantom.o:	nxtcommfantom.cpp
	$(CC) \
	-c \
	-I. -I$(INC_BIOS) -I$(INC_NXT) -I$(INC_FANTOM) \
	nxtcommfantom.cpp

