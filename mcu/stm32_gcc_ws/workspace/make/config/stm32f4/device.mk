#
# Rules to (help) build the F4xx device support.
#

#
# Directory containing this makefile
#
CONFIG_DIR			:=	$(dir $(lastword $(MAKEFILE_LIST)))

#
# Compiler options implied by the F4xx
#
CDEFS 				+= -DUSE_STDPERIPH_DRIVER
ARCHFLAGS			+= -mcpu=cortex-m4 -march=armv7e-m -mfpu=fpv4-sp-d16 -mfloat-abi=hard
FLOATABI			+= hard

#
# PIOS device library source and includes
#
include $(CONFIG_DIR)/cmsis.mk

#
# ST Peripheral library
#
# PERIPHLIB			 =	$(COMMONLIB_DIR)/STM32F4xx_StdPeriph_Driver
# EXTRAINCDIRS		+=	$(PERIPHLIB)/inc
# SRC					+=	$(wildcard $(PERIPHLIB)/src/*.c)
include $(CONFIG_DIR)/stdperiph.mk

# #
# # ST USB OTG library
# #
# USBOTGLIB			=	$(CONFIG_DIR)/Libraries/STM32_USB_OTG_Driver
# USBOTGLIB_SRC			=	usb_core.c usb_dcd.c usb_dcd_int.c
# EXTRAINCDIRS			+=	$(USBOTGLIB)/inc
# SRC				+=	$(addprefix $(USBOTGLIB)/src/,$(USBOTGLIB_SRC))

# #
# # ST USB Device library
# #
# USBDEVLIB			=	$(CONFIG_DIR)/Libraries/STM32_USB_Device_Library
# EXTRAINCDIRS			+=	$(USBDEVLIB)/Core/inc
# SRC				+=	$(wildcard $(USBDEVLIB)/Core/src/*.c)

