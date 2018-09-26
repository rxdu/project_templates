# FreeRTOS
FREERTOS := $(COMMONLIB_DIR)/FreeRTOS/Source

SRC	+=	$(wildcard $(FREERTOS)/*.c)
SRC	+=	$(wildcard $(FREERTOS)/portable/GCC/ARM_CM4F/*.c)
SRC	+=	$(FREERTOS)/portable/MemMang/heap_1.c

EXTRAINCDIRS += $(FREERTOS)/include
EXTRAINCDIRS += $(FREERTOS)/portable/GCC/ARM_CM4F