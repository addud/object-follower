# Target
TARGET = tribot_rc

# path to NXTway-GS++ sample to re-use drivers classes
NXTWAY_GS_DIR = NXTway_GS++
# include path
USER_INC_PATH= ../$(NXTWAY_GS_DIR)

# C++(.cpp) source files
TARGET_CPP_SOURCES = \
	../$(NXTWAY_GS_DIR)/DriverManager.cpp \
	../$(NXTWAY_GS_DIR)/GamePadDriver.cpp \
	sample.cpp

# TOPPERS/ATK(OSEK) config file
TOPPERS_OSEK_OIL_SOURCE = sample.oil

# don't change this macro
O_PATH ?= build
# to clean up the dir which was created outside of O_PATH
# CAUTION: Directry specified by USER_O_PATH is removed without any confirmation, thus if the specified dir pointed unexpected
# directory due to some mistake, it would be the cause of some disaster.  
USER_O_PATH = ./$(NXTWAY_GS_DIR)

# makefile for C++(.cpp) build
include ../../../ecrobot/ecrobot++.mak
