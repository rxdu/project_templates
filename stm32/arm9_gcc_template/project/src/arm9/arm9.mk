## Platform root directory
PLATFORM_DIR = $(SRC_DIR)/arm9

# Hardware component config
PLATFORM          ?= ARM9
USE_FPU  		  ?= 1
MCU_NAME		   = STM32F405RG

## Library components

## Project specific configurations
# inc/src directories
INCLUDES += -I$(PLATFORM_DIR)
INCLUDES += -I$(PLATFORM_DIR)/config
VPATH += $(PLATFORM_DIR)
VPATH += $(PLATFORM_DIR)/system

# sub-modules
# include $(PLATFORM_DIR)/driver/driver.mk
# include $(PLATFORM_DIR)/tasks/tasks.mk

# targets
CRT0_OBJ = startup.o system_init.o tiny_printf.o
PROJ_OBJ += main.o

## Compiling flags
#STFLAGS = -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000

## Linking flags
LINKER_FILE = $(PLATFORM_DIR)/arm968_flash.ld
LOAD_ADDRESS = 0x8000000

#include $(PLATFORM_DIR)/debug.mk
