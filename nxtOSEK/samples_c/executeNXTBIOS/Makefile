# Target specific macros
TARGET = execNXTBIOS
TARGET_SOURCES = \
	sample.c
TOPPERS_OSEK_OIL_SOURCE = ./sample.oil

# Compile switches
# Defining NO_RUN_ENTER_STOP_EXIT macro allows to disable initial display and RUN/STOP/ENTER/STOP buttons.
USER_DEF = NO_RUN_ENTER_STOP_EXIT

# Don't modify below part
O_PATH ?= build
include ../../ecrobot/ecrobot.mak
