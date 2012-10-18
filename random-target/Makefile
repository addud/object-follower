# Name of target
TARGET = random

# NXTOSEK root path
NXTOSEKROOT = ../nxtOSEK

########################################################################

#Target source
TARGET_SOURCES := \
        $(TARGET).c
TOPPERS_OSEK_OIL_SOURCE := ./$(TARGET).oil

PATH := $(WINEPATH):$(PATH)

O_PATH ?= build

include $(NXTOSEKROOT)/ecrobot/ecrobot.mak
