# Target specific macros
TARGET = largeprgtest
TARGET_SOURCES := \
	largeprgtest.c \
	map.c
TOPPERS_OSEK_OIL_SOURCE := ./largeprgtest.oil

# BUILD_MODE is not defined(default): build binaries for Flash and SRAM
# BUILD_MODE = Flash_only: build binary for only Flash
# BUILD_MODE = SRAM_only: build binary for only SRAM
BUILD_MODE = ROM_ONLY

O_PATH ?= build

include ../../ecrobot/ecrobot.mak
