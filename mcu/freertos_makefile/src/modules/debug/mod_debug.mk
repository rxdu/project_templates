DEBUG_MOD = $(MOD_DIR)/debug

VPATH += $(DEBUG_MOD)
INCLUDES += -I$(DEBUG_MOD)

LIB_OBJ += jlink_rtt.o

# dependent on RTT library
include $(LIB_DIR)/RTT/rtt.mk