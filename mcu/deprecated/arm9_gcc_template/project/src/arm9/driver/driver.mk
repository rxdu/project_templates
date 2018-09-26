VPATH += $(PLATFORM_DIR)/driver
INCLUDES += -I$(PLATFORM_DIR)/driver

PROJ_OBJ += BK_Scheduler.o
PROJ_OBJ += exception.o
PROJ_OBJ += icu_drv.o
PROJ_OBJ += racerio_timer.o
