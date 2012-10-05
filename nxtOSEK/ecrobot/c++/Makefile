# Makefile for ECRobot C++(.cpp) library

ROOT = ../..

ECROBOT_ROOT = $(ROOT)/ecrobot
ECROBOT_C_ROOT = $(ROOT)/ecrobot/c
LEJOSNXJSRC_ROOT = $(ROOT)/lejos_nxj/src/
TOPPERS_OSEK_ROOT = $(ROOT)/toppers_osek
ECROBOT_CPP_ROOT = $(ECROBOT_ROOT)/c++

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
	$(ECROBOT_C_ROOT) \
	$(ECROBOT_CPP_ROOT)/device \
	$(ECROBOT_CPP_ROOT)/util

DEVICE_CPP_SOURCES = $(addprefix $(ECROBOT_CPP_ROOT)/device/, \
	AccelSensor.cpp \
	Bluetooth.cpp \
	Camera.cpp \
	Clock.cpp \
	ColorSensor.cpp \
	CompassSensor.cpp \
	GyroSensor.cpp \
	I2c.cpp \
	IrSeeker.cpp \
	Lcd.cpp \
	LegoLight.cpp \
	LightSensor.cpp \
	Motor.cpp \
	Nxt.cpp \
	PSPNx.cpp \
	RcxLightSensor.cpp \
	SonarSensor.cpp \
	SoundSensor.cpp \
	Speaker.cpp \
	TouchSensor.cpp \
	Usb.cpp \
	Rs485.cpp \
	NxtColorSensor.cpp)

UTIL_CPP_SOURCES =  $(addprefix $(ECROBOT_CPP_ROOT)/util/, \
	BTConnection.cpp \
	Daq.cpp \
	GamePad.cpp \
	New.cpp)

CPP_LIB_SOURCES = \
	$(DEVICE_CPP_SOURCES) \
	$(UTIL_CPP_SOURCES)

C_OPTIMISATION_FLAGS = -Os
include $(ECROBOT_ROOT)/tool_gcc.mak

O_FILES = $(CPP_LIB_SOURCES:cpp=o)

TARGET = $(ECROBOT_ROOT)/libecrobot++.a

.PHONY: all
all: $(TARGET)

$(TARGET): $(O_FILES)
	@echo "Creating $@"
	$(AR) rv $(TARGET) $(O_FILES)

%.o: %.c
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.cpp
	@echo "Compiling $< to $@"
	$(CXX) $(CXXFLAGS) -Weffc++ -Wold-style-cast -Wreturn-type -Wnon-virtual-dtor -Wsign-promo -Woverloaded-virtual -o $@ $<

.PHONY: release
release:
	rm $(O_FILES)

.PHONY: clean
clean:
	rm $(TARGET)
	rm $(O_FILES)

.PHONY: doxy
doxy:
	@echo "Generating html files by doxygen..."
	doxygen ./ecrobotdoc.cfg
