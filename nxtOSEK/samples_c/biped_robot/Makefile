# NXTe_ROOT macro needs to be adapted 
NXTe_ROOT = /cygdrive/C/cygwin/nxtOSEK/samples_c/nxte

# Target specific macros
TARGET = biped_robot
TARGET_SOURCES := \
	$(NXTe_ROOT)/nxte.c \
	sleep.c \
	motion.c \
	biped_robot.c
TOPPERS_OSEK_OIL_SOURCE := ./biped_robot.oil
USER_INC_PATH = $(NXTe_ROOT)

O_PATH ?= build

include ../../ecrobot/ecrobot.mak
