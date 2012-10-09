# Target specific macros
TARGET = nxt2

TARGET_CPP_SOURCES = sample.cpp
	
TOPPERS_OSEK_OIL_SOURCE = ./sample.oil

# Compile switches
# Defining NO_RUN_ENTER_STOP_EXIT macro allows to disable initial display and RUN/STOP/ENTER/STOP buttons.
USER_DEF = NO_RUN_ENTER_STOP_EXIT

# Don't modify below part
O_PATH ?= build

# makefile for C++(.cpp) build
include ../../../ecrobot/ecrobot++.mak
