# Makefile for LEJOS OSEK C/C++ library

ROOT = ../..

ECROBOT_ROOT = $(ROOT)/ecrobot
ECROBOT_C_ROOT = $(ROOT)/ecrobot/c
LEJOSNXJSRC_ROOT = $(ROOT)/lejos_nxj/src/
TOPPERS_OSEK_ROOT = $(ROOT)/toppers_osek
CXX_ROOT = $(ROOT)/c++

LEJOS_PLATFORM_SOURCES_PATH = nxtvm/platform/nxt
LEJOS_VM_SOURCES_PATH = nxtvm/javavm

TOPPERS_OSEK_INC_PATH = \
	$(TOPPERS_OSEK_ROOT)/kernel \
	$(TOPPERS_OSEK_ROOT)/include \
	$(TOPPERS_OSEK_ROOT)/config/at91sam7s-gnu \
	$(TOPPERS_OSEK_ROOT)/config/at91sam7s-gnu/lego_nxt \
	$(TOPPERS_OSEK_ROOT)/sg \
	$(TOPPERS_OSEK_ROOT)/syslib/at91sam7s-gnu/lego_nxt

TOPPERS_INC_PATH = $(TOPPERS_OSEK_INC_PATH)

INC_PATH := \
	$(LEJOSNXJSRC_ROOT)/$(LEJOS_PLATFORM_SOURCES_PATH) \
	$(LEJOSNXJSRC_ROOT)/$(LEJOS_VM_SOURCES_PATH) \
	$(ECROBOT_ROOT) \
	$(ECROBOT_C_ROOT) \
	$(CXX_ROOT)/boost \
	$(CXX_ROOT)/util

C_LIB_SOURCES = nxtAssert.c

CC_LIB_SOURCES = AccelSensor.cc ColorSensor.cc CompassSensor.cc LightSensor.cc \
	Motor.cc sensormonitor.cc sleep.cc SonarSensor.cc SoundSensor.cc timerint.cc TouchSensor.cc PrototypeSensor.cc \
	PSPNx.cc Sprite.cc Screen.cc


C_OPTIMISATION_FLAGS = -Os
include $(ECROBOT_ROOT)/tool_gcc.mak

O_FILES = $(C_LIB_SOURCES:c=o) $(CC_LIB_SOURCES:cc=o)

TARGET = $(CXX_ROOT)/liblejososek.a

.PHONY: all
all: $(TARGET)

$(TARGET): $(O_FILES)
	@echo "Creating $@"
	$(AR) rv $(TARGET) $(O_FILES)

%.o: %.c
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.cc
	@echo "Compiling $< to $@"
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: release
release:
	rm $(O_FILES)

.PHONY: clean
clean:
	rm $(TARGET)
	rm $(O_FILES)

