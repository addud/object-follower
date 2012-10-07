# Name of target
TARGET = follow

# NXTOSEK root path
NXTOSEKROOT = ../nxtOSEK

########################################################################

TARGET_SOURCES := \
        $(TARGET).c \
 	filter.c \
 	lib.c \
	camera.c
TOPPERS_OSEK_OIL_SOURCE := ./$(TARGET).oil

PATH := $(WINEPATH):$(PATH)

O_PATH ?= build

include $(NXTOSEKROOT)/ecrobot/ecrobot.mak
