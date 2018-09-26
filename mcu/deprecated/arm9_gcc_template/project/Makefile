# Makefile for STM32 GCC Template

# 	Modified by rdu, from the makefile of the crazyflie project
#			https://github.com/bitcraze/crazyflie-firmware/blob/master/Makefile

# 		CrazyFlie's Makefile
# 		Copyright (c) 2011,2012 Bitcraze AB

# 	This Makefile compiles all the objet file to ./bin/ and the resulting firmware
# 	image in ./cflie.elf and ./cflie.bin

# Put your personal build config in tools/make/config.mk and DO NOT COMMIT IT!
# Make a copy of tools/make/config.mk.example to get you started
#-include tools/make/config.mk

#CFLAGS += $(EXTRA_CFLAGS)

#Program name
PROG_PREFIX = demo
PROJECT_MAKEFILE = src/arm9/arm9.mk

PROG = $(PROG_PREFIX)_arm9

# Default hardware component config
PLATFORM          ?= ARM9
USE_FPU  		  ?= 1

############### Location configuration ################

### Location of libraries
SRC_DIR = src
MOD_DIR = $(SRC_DIR)/modules
LIB_DIR = $(SRC_DIR)/libraries

### user source/header file directories ###
# additional directories defined in specific projects
VPATH += src
INCLUDES += -Isrc

include $(PROJECT_MAKEFILE)

############### Build Object configuration ################

# Build objects
#		OBJ: combination of the following objects
#		- CRT0_OBJ: target specific objects for startup
#		- LIB_OBJ: objects of libaries
#		- PROJ_OBJ: project objects

# Init
OBJ = $(CRT0_OBJ)
OBJ += $(LIB_OBJ) $(MOD_OBJ) $(PROJ_OBJ) 

######### JTAG and environment configuration ##########

CROSS_COMPILE     ?= arm-none-eabi-
PYTHON2           ?= python2
DFU_UTIL          ?= dfu-util
DEBUG             ?= 0
RTOS_DEBUG        ?= 0

############### Complile and Link configuration ################

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy
GDB = $(CROSS_COMPILE)gdb

ifdef P
  C_PROFILE = -D P_$(P)
endif

PROCESSOR = -mcpu=arm968e-s
CFLAGS += -fno-math-errno

ifeq ($(DEBUG), 1)
  CFLAGS += -O0 -g3 -DDEBUG
else
  CFLAGS += -Os -g3
endif

ifeq ($(LTO), 1)
  CFLAGS += -flto
endif

CFLAGS += -std=c99
CFLAGS += $(PROCESSOR) $(INCLUDES) $(STFLAGS)
CFLAGS += -Wall -fno-strict-aliasing -Wno-unused-value $(C_PROFILE)
# Compiler flags to generate dependency files:
CFLAGS += -MD -MP -MF $(BIN)/dep/$(@).d -MQ $(@)
# Permits to remove un-used functions and global variables from output file
CFLAGS += -ffunction-sections -fdata-sections --specs=nano.specs 

ASFLAGS = $(PROCESSOR) $(INCLUDES)
LDFLAGS = $(PROCESSOR) -Wl,-Map=$(PROG).map,--cref,--gc-sections,--undefined=uxTopUsedPriority --specs=nano.specs
LDFLAGS += -T $(LINKER_FILE)

ifeq ($(LTO), 1)
  LDFLAGS += -Os -flto -fuse-linker-plugin
endif

#Where to compile the .o
BIN = bin
VPATH += $(BIN)

#Dependency files to include
DEPS := $(foreach o,$(OBJ),$(BIN)/dep/$(o).d)

##################### Misc. ################################

ifeq ($(SHELL),/bin/sh)
  COL_RED=\033[1;31m
  COL_GREEN=\033[1;32m
  COL_RESET=\033[m
endif

#################### Targets ###############################

all: build
build: compile print_version size
compile: $(PROG).hex $(PROG).bin $(PROG).dfu

#clean_version:
#ifeq ($(SHELL),/bin/sh)
#	@echo "  CLEAN_VERSION"
#	@rm -f version.c
#endif

print_version: compile
ifeq ($(PLATFORM), STM32F1)
	@echo "Firmware for $(PROG) build!"
endif
ifeq ($(PLATFORM), STM32F4)
	@echo "Firmware for $(PROG) build!"
endif
#	@$(PYTHON2) tools/python/versionTemplate.py --print-version

size: compile
	@$(SIZE) -B $(PROG).elf

#Print preprocessor #defines
prep:
	@$(CC) $(CFLAGS) -dM -E - < /dev/null

#check_submodules:
#	@$(PYTHON2) tools/make/check-for-submodules.py

###### Debugging ######
## Generic targets
gdb: $(PROG).elf
	$(GDB) -ex "target remote localhost:3333" -ex "monitor reset halt" $^

flash_dfu:
	$(DFU_UTIL) -a 0 -D $(PROG).dfu

## JLink targets
# In order to use JLink to load the code to Flash, you need the following 2 steps:
# 1. start a gdb server first: make start_gdb_server
# 2. load code and debug/run: make connect_gdb_server
jlink_gdb_server:
	JLinkGDBServer -if SWD -device $(MCU_NAME)

jlink_gdb_debug:
	$(GDB) -x ./scripts/jlink-debug.gdbinit $(PROG).elf

jlink_flash:
	JLinkExe -if SWD -device $(MCU_NAME) -speed 4000 -CommanderScript $(PLATFORM_DIR)/jlink-flash.jlink

#include actual build targets
include tools/targets.mk

#include dependencies
-include $(DEPS)
