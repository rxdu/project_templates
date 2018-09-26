## Platform root directory
PLATFORM_DIR = $(SRC_DIR)/racer_core

## Hardware component config
# Note: you have to make sure the following 3 variables 
#		are set correctly
PLATFORM          ?= STM32F4
USE_FPU  		  ?= 1
MCU_NAME		   = STM32F427VI

# Debugging config
DEBUG             ?= 1

## Library components
## CMSIS
include $(LIB_DIR)/CMSIS/CMSIS_$(PLATFORM)/cmsis.mk

# FreeRTOS
include $(LIB_DIR)/FreeRTOS/freertos.mk

# STM32F4 standard peripheral library
include $(LIB_DIR)/STM32F4xx_StdPeriph_Driver/stm32f4_stdperiph.mk

# Modules
include $(MOD_DIR)/debug/mod_debug.mk

## Project specific configurations
# inc/src directories
INCLUDES += -I$(PLATFORM_DIR)
INCLUDES += -I$(PLATFORM_DIR)/config
VPATH += $(PLATFORM_DIR)

# sub-modules
include $(PLATFORM_DIR)/driver/driver.mk
include $(PLATFORM_DIR)/tasks/tasks.mk

# targets
CRT0_OBJ = startup_stm32f427_437xx.o system_stm32f4xx.o
PROJ_OBJ += main.o

## Compiling flags
STFLAGS = -DSTM32F427_437xx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000

## Linking flags
LINKER_FILE = $(PLATFORM_DIR)/stm32f427_437xx_flash.ld
LOAD_ADDRESS = 0x8000000

#include $(PLATFORM_DIR)/debug.mk
