# st_obj.mk - Selection of the ST library objects to compile
# This file is adapted from the file from the Crazyflie project
# Copyright (c) 2009, EAT-IT

STM32F4_STDPERIPH_LIB = $(LIB_DIR)/STM32F4xx_StdPeriph_Driver

VPATH += $(STM32F4_STDPERIPH_LIB)/src/
INCLUDES += -I$(STM32F4_STDPERIPH_LIB)/inc

LIB_OBJ += misc.o
LIB_OBJ += stm32f4xx_adc.o
LIB_OBJ += stm32f4xx_can.o
LIB_OBJ += stm32f4xx_cec.o
LIB_OBJ += stm32f4xx_crc.o
LIB_OBJ += stm32f4xx_dac.o
LIB_OBJ += stm32f4xx_dbgmcu.o
LIB_OBJ += stm32f4xx_dma.o
LIB_OBJ += stm32f4xx_exti.o
LIB_OBJ += stm32f4xx_flash.o
LIB_OBJ += stm32f4xx_fsmc.o
LIB_OBJ += stm32f4xx_gpio.o
LIB_OBJ += stm32f4xx_i2c.o
LIB_OBJ += stm32f4xx_iwdg.o
LIB_OBJ += stm32f4xx_pwr.o
LIB_OBJ += stm32f4xx_rcc.o
LIB_OBJ += stm32f4xx_rtc.o
LIB_OBJ += stm32f4xx_sdio.o
LIB_OBJ += stm32f4xx_spi.o
LIB_OBJ += stm32f4xx_tim.o
LIB_OBJ += stm32f4xx_usart.o
LIB_OBJ += stm32f4xx_wwdg.o
