# Target
TARGET = nxtway_lt

NXTWAY_GS_DIR = NXTway_GS++

# include path
USER_INC_PATH= ../../../ecrobot/nxtway_gs_balancer ../$(NXTWAY_GS_DIR)

# library
USER_LIB = nxtway_gs_balancer

# C source file
TARGET_SOURCES = \
	../$(NXTWAY_GS_DIR)/balancer_param.c

# C++(.cpp) source files
TARGET_CPP_SOURCES = \
	../$(NXTWAY_GS_DIR)/NXTway_GS.cpp \
	../$(NXTWAY_GS_DIR)/StartStopDriver.cpp \
	../$(NXTWAY_GS_DIR)/SonarDriver.cpp \
	../$(NXTWAY_GS_DIR)/DriverManager.cpp \
	LineTraceDriver.cpp \
	sample.cpp

# TOPPERS/ATK(OSEK) config file
TOPPERS_OSEK_OIL_SOURCE = sample.oil

# don't change this macro
O_PATH ?= build
USER_O_PATH = ./$(NXTWAY_GS_DIR)

# makefile for C++(.cpp) build
include ../../../ecrobot/ecrobot++.mak
