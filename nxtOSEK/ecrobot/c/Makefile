# Makefile for ECRobot library

# modified to support new directory structure by takashic
ROOT := $(dir $(lastword $(MAKEFILE_LIST)))../..

ECROBOT_ROOT = $(ROOT)/ecrobot
LEJOSNXJSRC_ROOT = $(ROOT)/lejos_nxj/src/
TOPPERS_OSEK_ROOT = $(ROOT)/toppers_osek
LEJOS_PLATFORM_SOURCES_PATH = $(LEJOSNXJSRC_ROOT)/nxtvm/platform/nxt
LEJOS_VM_SOURCES_PATH = $(LEJOSNXJSRC_ROOT)/nxtvm/javavm

TOPPERS_OSEK_INC_PATH = \
	$(TOPPERS_OSEK_ROOT)/kernel \
	$(TOPPERS_OSEK_ROOT)/include \
	$(TOPPERS_OSEK_ROOT)/config/at91sam7s-gnu \
	$(TOPPERS_OSEK_ROOT)/config/at91sam7s-gnu/lego_nxt \
	$(TOPPERS_OSEK_ROOT)/sg \
	$(TOPPERS_OSEK_ROOT)/syslib/at91sam7s-gnu/lego_nxt

TOPPERS_INC_PATH = $(TOPPERS_OSEK_INC_PATH)

#
## LEJOS NXJ platform source
#
ifndef LEJOS_PLATFORM_SOURCES 
LEJOS_PLATFORM_SOURCES := $(addprefix $(LEJOS_PLATFORM_SOURCES_PATH)/, \
	uart.c \
	systick.c \
	byte_fifo.c \
	aic.c \
	udp.c \
	twi.c \
	nxt_spi.c \
	nxt_motors.c \
	data_abort.c \
	display.c \
	i2c.c \
	sound.c \
	flashprog.c \
	hs.c \
	bt.c )
endif

ifndef LEJOS_HOOK_SOURCES
LEJOS_HOOK_SOURCES := $(addprefix $(LEJOS_PLATFORM_SOURCES_PATH)/, \
	nxt_avr.c \
	sensors.c \
	sensors1.c \
	nxt_lcd.c )
endif

C_LIB_SOURCES = \
	ecrobot_mindsensors.c \
	ecrobot_rs485.c \
	ecrobot_usb.c \
	ecrobot_HiTechnic.c \
	ecrobot_device_hook.c \
	ecrobot_interface.c \
	NxtCam.c \
	colorsensor.c \
	osek_hook.c

C_LIB_RAMSOURCES := \
	$(LEJOS_PLATFORM_SOURCES) \
	$(LEJOS_HOOK_SOURCES) \
	$(ECROBOT_ROOT)/bios/flash_loader.c

S_LIB_SOURCES :=

S_LIB_RAMSOURCES := \
	$(LEJOS_PLATFORM_SOURCES_PATH)/interrupts.s

BMP_LIB_SOURCES := \
	nxtjsp_splash.bmp \
	nxtosek_splash.bmp

C_OPTIMISATION_FLAGS = -Os
include $(ECROBOT_ROOT)/tool_gcc.mak

INC_PATH := \
	$(LEJOS_PLATFORM_SOURCES_PATH) \
	$(LEJOS_VM_SOURCES_PATH) \
	$(TOPPERS_INC_PATH) \
	$(ECROBOT_ROOT)/bios \
	$(ECROBOT_ROOT)

O_FILES = $(C_LIB_SOURCES:c=o) $(C_LIB_RAMSOURCES:c=oram) $(S_LIB_SOURCES:s=o) $(S_LIB_RAMSOURCES:s=oram) $(BMP_LIB_SOURCES:bmp=obmp)

TARGET = $(ECROBOT_ROOT)/libecrobot.a

.PHONY: all
all: $(TARGET) 

$(TARGET): $(O_FILES)
	@echo "Creating $@"
	$(AR) rv $(TARGET) $(O_FILES)

%.o: %.c
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -o $@ $<

%.oram: %.c
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.s
	@echo "Assembling $< to $@"
	$(AS) $(ASFLAGS) -o $@ $<

%.oram: %.s
	@echo "Assembling $< to $@"
	$(AS) $(ASFLAGS) -o $@ $<

%.obmp : %.bmp
	@echo "Converting $< to $@"
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm \
	--redefine-sym _binary_$(basename $(notdir $<))_bmp_start=$(basename $(notdir $<))_bmp_start \
	--redefine-sym _binary_$(basename $(notdir $<))_bmp_end=$(basename $(notdir $<))_bmp_end \
	--redefine-sym _binary_$(basename $(notdir $<))_bmp_size=$(basename $(notdir $<))_bmp_size \
	$< $@

.PHONY: release
release:
	rm $(O_FILES)

.PHONY: clean
clean:
	rm $(TARGET)
	rm $(O_FILES)

