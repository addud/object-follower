# Target specific macros
TARGET = NXTway_GS_OSEK

NXTOSEK_ROOT = ../..

# nxtway_gs_balancer library desiged for NXTway-GS two wheeled self-balancing robot
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer
USER_LIB = nxtway_gs_balancer

# using NXT standard tires (not Motorcycle tires)
#USER_DEF = NXT_STD_TIRE

# User application source
TARGET_SOURCES := \
	balancer_param.c \
	nxtway_gs.c

# OSEK OIL file
TOPPERS_OSEK_OIL_SOURCE := ./nxtway_gs.oil

# below part should not be modified
O_PATH ?= build
include $(NXTOSEK_ROOT)/ecrobot/ecrobot.mak
