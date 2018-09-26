# CMSIS source path
CMSIS_DIR = $(LIB_DIR)/CMSIS/CMSIS_$(PLATFORM)

VPATH += $(CMSIS_DIR)/Device/ST/STM32F4xx/Source/
VPATH += $(CMSIS_DIR)/Device/ST/STM32F4xx/Source/startup

INCLUDES += -I$(CMSIS_DIR)/Include
INCLUDES += -I$(CMSIS_DIR)/Device/ST/STM32F4xx/Include