VPATH += $(PLATFORM_DIR)/driver
INCLUDES += -I$(PLATFORM_DIR)/driver

PROJ_OBJ += racerio_driver.o
PROJ_OBJ += racerio_gpio.o
PROJ_OBJ += racerio_can.o
PROJ_OBJ += racerio_timer.o
