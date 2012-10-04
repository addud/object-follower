# Makefile for NXT BIOS

TARGET = nxt_bios

TARGET_SOURCES := \
	bios_display.c \
	bios.c

O_PATH ?= build

#
## ROOT path configurations
#
ROOT := $(dir $(lastword $(MAKEFILE_LIST)))../..

ECROBOT_ROOT = $(ROOT)/ecrobot
# added to support new directory structure by takshic
ECROBOT_C_ROOT = $(ECROBOT_ROOT)/c

LEJOSNXJSRC_ROOT = $(ROOT)/lejos_nxj/src/

vpath %.c $(LEJOSNXJSRC_ROOT) $(ECROBOT_ROOT)/bios
vpath %.S $(LEJOSNXJSRC_ROOT)
vpath %.s $(LEJOSNXJSRC_ROOT) $(ECROBOT_ROOT)/bios

#
## LEJOS NXJ include path
#
LEJOS_PLATFORM_SOURCES_PATH = nxtvm/platform/nxt
LEJOS_VM_SOURCES_PATH = nxtvm/javavm

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
	bt.c )
endif

ifndef LEJOS_HOOK_SOURCES
LEJOS_HOOK_SOURCES := $(addprefix $(LEJOS_PLATFORM_SOURCES_PATH)/, \
	nxt_avr.c \
	sensors.c \
	nxt_lcd.c )
endif

C_SOURCES := \
	$(TARGET_SOURCES)

C_RAMSOURCES := \
	$(LEJOS_PLATFORM_SOURCES) \
	$(LEJOS_HOOK_SOURCES) \
	$(LEJOS_PLATFORM_SOURCES_PATH)/flashprog.c \
	$(ECROBOT_C_ROOT)/ecrobot_usb.c \
	flash_loader.c

S_SOURCES := \
	$(LEJOS_PLATFORM_SOURCES_PATH)/vectors.s \
	init.s

S_RAMSOURCES := \
	$(LEJOS_PLATFORM_SOURCES_PATH)/interrupts.s \
	$(LEJOS_PLATFORM_SOURCES_PATH)/irq.s

# using the new linker script
LDSCRIPT_SOURCE := ./sam7_bios.lds

C_OPTIMISATION_FLAGS = -Os
include $(ECROBOT_ROOT)/tool_gcc.mak

INC_PATH := \
	$(LEJOSNXJSRC_ROOT)/$(LEJOS_PLATFORM_SOURCES_PATH) \
	$(LEJOSNXJSRC_ROOT)/$(LEJOS_VM_SOURCES_PATH) \
	$(ECROBOT_C_ROOT)

PHONY: EnvironmentMessage
EnvironmentMessage:
	@echo " CC      $(CC)"
	@echo " CPP     $(CPP)"
	@echo " AS      $(AS)"
	@echo " AR      $(AR)"
	@echo " LD      $(LD)"
	@echo " OBJCOPY $(OBJCOPY)"

RAM_TARGET   := $(TARGET)_ram.elf
ROM_TARGET   := $(TARGET)_rom.elf
SAMBA_TARGET := $(TARGET)_samba_ram.bin
ROMBIN_TARGET := $(TARGET)_rom.rfw

RAM_LDSCRIPT   := $(O_PATH)/$(TARGET)_ram.ld
ROM_LDSCRIPT   := $(O_PATH)/$(TARGET)_rom.ld
SAMBA_LDSCRIPT := $(O_PATH)/$(TARGET)_samba.ld

S_OBJECTS := $(addprefix $(O_PATH)/,$(S_SOURCES:.s=.o) $(S_RAMSOURCES:.s=.oram))
C_OBJECTS := $(addprefix $(O_PATH)/,$(C_SOURCES:.c=.o) $(C_RAMSOURCES:.c=.oram))

dependencies = $(subst .o,.d,$(C_OBJECTS) $(S_OBJECTS) )

def_target: all


ALL_TARGETS := $(RAM_TARGET) $(ROM_TARGET) $(ROMBIN_TARGET) $(SAMBA_TARGET)


.PHONY:  all
#all:  BuildMessage $(ALL_TARGETS)
all:  $(ALL_TARGETS)

PHONY: TargetMessage
TargetMessage:
	@echo ""
	@echo "Building: $(ALL_TARGETS)"
	@echo ""
	@echo "C sources: $(C_SOURCES) to $(C_OBJECTS)"
	@echo ""
	@echo "C++ sources: $(CC_SOURCES) to $(CC_OBJECTS)"
	@echo ""
	@echo "Assembler sources: $(S_SOURCES) to $(S_OBJECTS)"
	@echo ""
	@echo "LD source: $(LDSCRIPT_SOURCE)"
	@echo ""

.PHONY: BuildMessage
BuildMessage: TargetMessage EnvironmentMessage

$(SAMBA_LDSCRIPT): $(LDSCRIPT_SOURCE)
	sed -e 's/^SAMBA_ONLY//' -e '/^RAM_ONLY/d' -e'/^ROM_ONLY/d' $< >$@

$(RAM_LDSCRIPT): $(LDSCRIPT_SOURCE)
	sed -e 's/^RAM_ONLY//' -e'/^ROM_ONLY/d' -e'/^SAMBA_ONLY/d' $< >$@

$(ROM_LDSCRIPT): $(LDSCRIPT_SOURCE)
	sed -e 's/^ROM_ONLY//' -e'/^RAM_ONLY/d' -e'/^SAMBA_ONLY/d' $< >$@

$(SAMBA_TARGET)_elf: $(C_OBJECTS) $(S_OBJECTS) $(SAMBA_LDSCRIPT)
	@echo "Linking $@"
	$(LINK_ELF) $(LDFLAGS)

$(RAM_TARGET): $(C_OBJECTS) $(S_OBJECTS) $(RAM_LDSCRIPT)
	@echo "Linking $@"
	$(LINK_ELF)

$(ROM_TARGET): $(C_OBJECTS) $(S_OBJECTS) $(ROM_LDSCRIPT)
	@echo "Linking $@"
	$(LINK_ELF)

$(ROMBIN_TARGET): $(ROM_TARGET)
	@echo "Generating binary file $@"
	$(OBJCOPY) -O binary $< $@

$(SAMBA_TARGET): $(SAMBA_TARGET)_elf
	@echo "Generating binary file $@"
	$(OBJCOPY) -O binary $< $@

.PHONY: release
release:  
	@rm -rf $(O_PATH)
	@rm -rf ../ecrobot
	@echo "Removing unnecessity targets"
	@rm -f $(RAM_TARGET) $(ROM_TARGET) $(SAMBA_TARGET)
	@echo "Removing map files"
	@rm -f *map
	@rm -f *.bin_elf

.PHONY: clean
clean:  
	@echo "Removing All Objects"
	@rm -rf $(O_PATH)
	@rm -rf ../ecrobot
	@echo "Removing target"
	@rm -f $(ALL_TARGETS)
	@echo "Removing map files"
	@rm -f *map
	@rm -f *.bin_elf

ifneq "$(MAKECMDGOALS)" "clean"
  -include $(dependencies)
endif

