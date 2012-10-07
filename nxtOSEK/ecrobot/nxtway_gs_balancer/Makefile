# Makefile for NXTway-GS balancer library

# modified to support new directory structure by takshic
ROOT := $(dir $(lastword $(MAKEFILE_LIST)))../..

ECROBOT_ROOT = $(ROOT)/ecrobot
# added to support new directory structure by takshic
ECROBOT_C_ROOT = $(ECROBOT_ROOT)/c

LEJOSNXJSRC_ROOT = $(ROOT)/lejos_nxj/src/

LEJOS_PLATFORM_SOURCES_PATH = $(LEJOSNXJSRC_ROOT)/nxtvm/platform/nxt
LEJOS_VM_SOURCES_PATH = $(LEJOSNXJSRC_ROOT)/nxtvm/javavm

C_LIB_SOURCES = \
	balancer.c

C_OPTIMISATION_FLAGS = -Os
include $(ECROBOT_ROOT)/tool_gcc.mak

INC_PATH := \
	$(LEJOS_PLATFORM_SOURCES_PATH) \
	$(LEJOS_VM_SOURCES_PATH) \
	$(ECROBOT_ROOT) \
	$(ECROBOT_C_ROOT)

O_FILES = $(C_LIB_SOURCES:c=o) 

TARGET = $(ECROBOT_ROOT)/libnxtway_gs_balancer.a

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
	$< $@

.PHONY: release
release:
	rm $(O_FILES)

.PHONY: clean
clean:
	rm $(TARGET)
	rm $(O_FILES)

