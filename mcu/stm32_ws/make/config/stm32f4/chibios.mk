#
# Rules to add ChibiOS/RT to a PiOS target
#
# Note that the PIOS target-specific makefile will detect that CHIBIOS_DIR
# has been defined and add in the target-specific pieces separately.
#

# ChibiOS
CHIBIOS := $(COMMONLIB_DIR)/ChibiOS

include $(CHIBIOS)/os/hal/ports/STM32/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk

SRC += $(PLATFORMSRC)
SRC += $(HALSRC)
SRC += $(PORTSRC)
SRC += $(KERNSRC)

EXTRAINCDIRS += $(PLATFORMINC)
EXTRAINCDIRS += $(HALINC)
EXTRAINCDIRS += $(PORTINC)
EXTRAINCDIRS += $(KERNINC)

