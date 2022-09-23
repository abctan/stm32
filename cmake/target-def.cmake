##########################################################################
# 设置编译工具链名称
set(CROSS_COMPILE_PREFIX "arm-none-eabi-")

# Target-specific flags
set(MCU_ARCH   ARMCM3)
set(MCU_FAMILY STM32F103xE)
set(MCU_NAME   STM32F103ZE)

# You can find the following values from ./cubemx/Makefile
set(CPU "-mcpu=cortex-m3")
set(FPU "")
set(FLOAT_ABI "")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/source/boot/STM32F103XE_FLASH.ld)
set(PROJ_LIB_PATH ${CMAKE_SOURCE_DIR}/source/libraries)
set(HAL_CONF_PATH ${CMAKE_SOURCE_DIR}/source/app/main)

option(USE_LL_LIB      "Enable LL library" ON)
option(USE_HAL_LIB     "Enable HAL library" ON)
option(USE_HAL_LEGACY  "Enable LEGACY library" ON)
option(USE_SYSTEM_VIEW "Enable Segger SystemView library" OFF)

# 可执行文件输出目录
set(EXE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output/target)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
##########################################################################