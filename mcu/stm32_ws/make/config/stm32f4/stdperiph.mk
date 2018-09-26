# st_obj.mk - Selection of the ST library objects to compile
# This file is adapted from the file from the Crazyflie project
# Copyright (c) 2009, EAT-IT

STDPERIPH_DIR = $(COMMONLIB_DIR)/STM32F4xx_StdPeriph_Driver

SRC += $(STDPERIPH_DIR)/src/misc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_adc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_can.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_cec.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_crc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_cryp.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_cryp_aes.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_cryp_des.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_cryp_tdes.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dac.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dbgmcu.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dcmi.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dfsdm.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dma.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dma2d.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_dsi.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_exti.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_flash.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_flash_ramfunc.c
# SRC += $(STDPERIPH_DIR)/src/stm32f4xx_fmc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_fmpi2c.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_fsmc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_gpio.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_hash.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_hash_md5.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_hash_sha1.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_i2c.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_iwdg.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_lptim.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_ltdc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_pwr.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_qspi.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_rcc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_rng.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_rtc.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_sai.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_sdio.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_spdifrx.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_spi.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_syscfg.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_tim.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_usart.c
SRC += $(STDPERIPH_DIR)/src/stm32f4xx_wwdg.c

EXTRAINCDIRS += $(STDPERIPH_DIR)/inc
