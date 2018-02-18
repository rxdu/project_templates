## Platform root directory
PLATFORM_DIR = $(SRC_DIR)/racerio

# Hardware component config
PLATFORM          ?= STM32F4
USE_FPU  		  ?= 1
MCU_NAME		   = STM32F405RG

## CMSIS
VPATH += $(LIB_DIR)/CMSIS/STM32F4xx/Source/
VPATH += $(LIB_DIR)/CMSIS/Device/ST/STM32F4xx/Source/

INCLUDES += -I$(LIB_DIR)/CMSIS/Include
INCLUDES += -I$(LIB_DIR)/CMSIS/Device/ST/STM32F4xx/Include

## Library components
# FreeRTOS
include $(LIB_DIR)/FreeRTOS/freertos.mk

# STM32F4 standard peripheral library
include $(LIB_DIR)/STM32F4xx_StdPeriph_Driver/stm32f4_stdperiph.mk

# Modules
include $(MOD_DIR)/debug/mod_debug.mk

## Project specific configurations
# include directories
INCLUDES += -I$(PLATFORM_DIR)/config
INCLUDES += -I$(PLATFORM_DIR)/user

# source directories
VPATH += $(PLATFORM_DIR)/user

# targets
CRT0_OBJ = startup_stm32f40xx.o system_stm32f4xx.o
PROJ_OBJ = main.o

## Compiling flags
STFLAGS = -DSTM32F4_PLATFORM -DSTM32F4XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000

## Linking flags
LINKER_FILE = $(PLATFORM_DIR)/stm32f405_flash.ld
LOAD_ADDRESS = 0x8000000

#include $(PLATFORM_DIR)/debug.mk
