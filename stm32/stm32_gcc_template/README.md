# STM32 GCC Project Template

## How to use the template

1. Copy src/demo to start a new project, for example src/my_proj
2. Rename the project makefile (demo.mk -> my_proj.mk), and then update configurations in src/my_proj/my_proj.mk
3. Update root makefile project/Makefile: set PROJECT_MAKEFILE to be "src/demo/my_proj.mk"

## Known limitations

* Only STM32F1/F4 targets are tested. However it should be easy to add support for other Cortex-M MCUs with minor modifications.
* ST-Link support to be added. 