## JLink targets
# In order to use JLink to load the code to Flash, you need the following 2 steps:
# 1. start a gdb server first: make start_gdb_server
# 2. load code and debug/run: make connect_gdb_server

MCU_NAME ?= STM32F405RG

.PHONY: jlink_gdb_server jlink_gdb_debug jlink_flash
jlink_gdb_server:
	JLinkGDBServer -if SWD -device $(MCU_NAME)

jlink_gdb_debug:
	$(GDB) -x ./scripts/jlink-debug.gdbinit $(PROG).elf

jlink_flash:
	JLinkExe -if SWD -device $(MCU_NAME) -speed 4000 -CommanderScript $(PLATFORM_DIR)/jlink-flash.jlink