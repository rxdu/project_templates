## Segway Robot Firmware

### 1. Directory structure

* src: source code, including 3rd party libraries
* inc: global header files
* scripts: scripts used to compile, upload
* tools: tools used for target make
* bin: folder reserved for object/temporary files during make

**Note**:
* startup code is put inside the CMSIS folder, under STM32F1xx/STM32F4xx for according target.
* linker scripts are put in scripts folder, under stm32f103/stm32f429.
* please check the version of included library before the first time use. It's easier to update the library at the early phase of the project.

### 2. Make targets

* Make default/clean

```
$ cd balancing_robot/firmware
$ make
$ make clean
```

* Download hex file to board

```
$ make jlink_flash_f1
```

Refer to Segger UM08001, Section 3.2.1 for more available commands for the script.

* Debugging with JLink using GDB

    * first start the gdb server
   ```
   $ make start_gdb_server
   ```

    * then connect to the gdb server and start debug session  in a different terminal

   ```
   $ make connect_gdb_server
   ```

* Debugging with ST-Link
    * first start the st-util
   ```
   $ make start_st_util
   ```

    * then start the debug session in a different terminal
   ```
   $ make debug_with_stlink
   ```

### 3. SEGGER RTT Debugging

* Set "SEGGER_RTT_DEBUG" to be 0 to disable RTT debugging.
* Use rtt_debug.h header instead of the headers from RTT library to more conveniently exclude RTT debugging related code when releasing code.
* Expose more functions in rtt_debug.h if needed.
* Use JLinkRTTClient (bundled with JLink software package) to listen to debugging information (You need to start the JLink GDB server first.).

## Reference:

GDB Commands

   * [Application Note by rdu](http://wiki.rdu.im/_pages/Projects/Application-Notes/Software/gdb.html)
