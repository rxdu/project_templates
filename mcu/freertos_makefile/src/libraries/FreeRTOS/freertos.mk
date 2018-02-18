# st_obj.mk - Selection of the ST library objects to compile
# This file is adapted from the file from the Crazyflie project
# Copyright (c) 2009, EAT-IT

# FreeRTOS source path
FREERTOS = $(LIB_DIR)/FreeRTOS/Source

ifeq ($(USE_FPU), 1)
PORT = $(FREERTOS)/portable/GCC/ARM_CM4F
else
PORT = $(FREERTOS)/portable/GCC/ARM_CM3
endif

INCLUDES += -I$(FREERTOS)/include 
INCLUDES += -I$(PORT)

VPATH += $(FREERTOS)
VPATH += $(PORT)
VPATH += $(FREERTOS)/portable/MemMang

MEMMANG_OBJ = heap_1.o
LIB_OBJ += list.o tasks.o queue.o timers.o port.o $(MEMMANG_OBJ)