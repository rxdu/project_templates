###############################################################################
# @file       Makefile
# @author     Tau Labs, http://taulabs.org, Copyright (C) 2012-2015
# @addtogroup 
# @{
# @addtogroup 
# @{
# @brief Makefile to build firmware for the Sparky2 board.
###############################################################################
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

include $(MAKE_INC_DIR)/firmware-defs.mk
include $(BOARD_ROOT_DIR)/board-info.mk

# Set developer code and compile options
# Set to YES for debugging
DEBUG ?= YES
ERASE_FLASH ?= NO
RTOS ?= FREERTOS

# List of modules to include
MODULES = rtt
MODULES += Attitude

PYMODULES = 

OPTMODULES += GPS

# Paths
TARGET_ARCHITECTURE = stm32f4

# Set platform/board paths
BOARD_FW_DIR = $(BOARD_ROOT_DIR)/firmware
PLATFORM_CONFIG_DIR = $(MAKE_INC_DIR)/config/$(TARGET_ARCHITECTURE)

## Source code 
SRC =
ASRC =

# any additional .c/.S files should be added after this line

# optional component libraries
# include $(FLIGHTLIB)/CMSIS3/DSP_Lib/library.mk
# include $(FLIGHTLIB)/lqg_rate/library.mk

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files

## MODULES
SRC += ${foreach MOD, ${MODULES} ${OPTMODULES}, ${wildcard ${OPMODULEDIR}/${MOD}/*.c}}
## OPENPILOT CORE:
SRC += main.c

# ifeq ($(DEBUG),YES)
# CM3_DEBUG_DIR = $(COMMONLIB_DIR)/CM3_Debug
# SRC += $(CM3_DEBUG_DIR)/dcc_stdio.c
# SRC += $(CM3_DEBUG_DIR)/cm3_fault_handlers.c
# EXTRAINCDIRS += $(CM3_DEBUG_DIR)
# endif

ifeq ($(ERASE_FLASH), YES)
CDEFS += -DERASE_FLASH
endif

# List C source files here which must be compiled in ARM-Mode (no -mthumb).
# use file-extension c for "c-only"-files
## just for testing, timer.c could be compiled in thumb-mode too
SRCARM =

# List C++ source files here.
# use file-extension .cpp for C++-files (not .C)
CPPSRC =

# List C++ source files here which must be compiled in ARM-Mode.
# use file-extension .cpp for C++-files (not .C)
#CPPSRCARM = $(TARGET).cpp
CPPSRCARM =

# List Assembler source files here.
# Make them always end in a capital .S. Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC = $

# List Assembler source files here which must be assembled in ARM-Mode..
ASRCARM =

EXTRAINCDIRS += ${foreach MOD, ${MODULES} ${OPTMODULES} ${PYMODULES}, $(OPMODULEDIR)/${MOD}}
EXTRAINCDIRS += ${foreach MOD, ${MODULES} ${OPTMODULES} ${PYMODULES}, $(OPMODULEDIR)/${MOD}/inc}

# List any extra directories to look for include files here.
#    Each directory must be seperated by a space.
EXTRAINCDIRS  += $(BOARD_FW_DIR)
EXTRAINCDIRS  += $(BOARD_FW_DIR)/config

# List any extra directories to look for library files here.
# Also add directories where the linker should search for
# includes from linker-script to the list
#     Each directory must be seperated by a space.
EXTRA_LIBDIRS =

# Extra Libraries
#    Each library-name must be seperated by a space.
#    i.e. to link with libxyz.a, libabc.a and libefsl.a:
#    EXTRA_LIBS = xyz abc efsl
# for newlib-lpc (file: libnewlibc-lpc.a):
#    EXTRA_LIBS = newlib-lpc
EXTRA_LIBS =

# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)

ifeq ($(DEBUG),YES)
CFLAGS += -O0
CFLAGS += -DGENERAL_COV
CFLAGS += -ffixed-r10
# CFLAGS += -finstrument-functions -ffixed-r10 # see dronin Makefile
else
CFLAGS += -Os
endif
   
# common architecture-specific flags from the device-specific library makefile
CFLAGS += $(ARCHFLAGS)

CFLAGS += -DDIAGNOSTICS
CFLAGS += -DDIAG_TASKS

# configure CMSIS DSP Library
CDEFS += -DARM_MATH_CM4
CDEFS += -DARM_MATH_MATRIX_CHECK
CDEFS += -DARM_MATH_ROUNDING
CDEFS += -D__FPU_PRESENT=1
CDEFS += -DUNALIGNED_SUPPORT_DISABLE

# This is not the best place for these.  Really should abstract out
# to the board file or something
CFLAGS += -D$(STM32_TYPE)
CFLAGS += -DMEM_SIZE=1024000000

# Output format. (can be ihex or binary or both)
#  binary to create a load-image in raw-binary format i.e. for SAM-BA,
#  ihex to create a load-image in Intel hex format
#LOADFORMAT = ihex
#LOADFORMAT = binary
LOADFORMAT = both

# Debugging format.
DEBUGF = dwarf-2

# Place project-specific -D (define) and/or
# -U options for C here.
CDEFS += -DHSE_VALUE=$(OSCILLATOR_FREQ)
CDEFS += -DSYSCLK_FREQ=$(SYSCLK_FREQ)
CDEFS += -DUSE_STDPERIPH_DRIVER
CDEFS += -DUSE_$(BOARD)
# CDEFS += -DCORTEX_VTOR_INIT='($(FW_BANK_BASE) - $(EF_BANK_BASE))'

# Declare all non-optional modules as built-in to force inclusion
get_mod_name = $(shell echo $(1) | sed "s/\/[^\/]*$///")
BUILTIN_DEFS := ${foreach MOD, ${MODULES}, -DMODULE_$(call get_mod_name, $(MOD))_BUILTIN }
CDEFS += ${BUILTIN_DEFS}

# Place project-specific -D and/or -U options for
# Assembler with preprocessor here.
#ADEFS = -DUSE_IRQ_ASM_WRAPPER
ADEFS = -D__ASSEMBLY__

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

#-----

# Compiler flags.

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)

ifeq ($(DEBUG),YES)
CFLAGS += -g$(DEBUGF)
endif

CFLAGS += -ffast-math

CFLAGS += -mcpu=$(MCU)
CFLAGS += $(CDEFS)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS)) -I.

CFLAGS += -mapcs-frame
CFLAGS += -fomit-frame-pointer
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wdouble-promotion

CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wa,-adhlns=$(addprefix $(OUTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
# Compiler flags to generate dependency files:
CFLAGS += -MD -MP -MF $(OUTDIR)/dep/$(@F).d

# flags only for C
#CONLYFLAGS += -Wnested-externs
CONLYFLAGS += $(CSTANDARD)

# Assembler flags.
#  -Wa,...:    tell GCC to pass this to the assembler.
#  -ahlns:     create listing
ASFLAGS  = $(ARCHFLAGS) -mthumb -I. -x assembler-with-cpp
ASFLAGS += $(ADEFS)
ASFLAGS += -Wa,-adhlns=$(addprefix $(OUTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
ASFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

MATH_LIB = -lm

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -nostartfiles -Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref,--gc-sections
LDFLAGS += $(patsubst %,-L%,$(EXTRA_LIBDIRS))
LDFLAGS += -lc
LDFLAGS += $(patsubst %,-l%,$(EXTRA_LIBS))
LDFLAGS += $(MATH_LIB)
LDFLAGS += -lc -lgcc
LDFLAGS += -Wl,--warn-common
LDFLAGS += -Wl,--fatal-warnings

# Linker scripts                                                                                                                                                                                                              
LDFLAGS += -T $(BOARD_ROOT_DIR)/scripts/stm32f405_flash.ld

# 01. Include startup code
ASRC += $(CMSIS_DIR)/Device/ST/STM32F4xx/Source/startup_stm32f40xx.S

# 02. Include target specific code
include $(BOARD_FW_DIR)/driver/driver.mk
include $(BOARD_FW_DIR)/tasks/tasks.mk

# 03. Include common code 
# Code building is invoked inside firmware-common.mk, so include this file at the end
include $(MAKE_INC_DIR)/firmware-common.mk
