# include define config
include(${CMAKE_SOURCE_DIR}/cmake/target-def.cmake)
# include gcc config
include(${CMAKE_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)

## auto-set variables from user input
set(MCU_FLAGS  "${CPU} -mthumb ${FPU} ${FLOAT_ABI}")
set(LINK_FLAGS "${MCU_FLAGS} -Wl,--gc-sections")
set(EXTRA_LINK_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch -specs=nano.specs -specs=nosys.specs")

# Define compilation macros
add_definitions(-D${MCU_FAMILY})
if (${USE_HAL_LIB})
    add_definitions(-DUSE_HAL_DRIVER)
endif()
if (${USE_LL_LIB})
    add_definitions(-DUSE_FULL_LL_DRIVER)
endif()
if (${USE_HAL_LEGACY})
    add_definitions(-DUSE_HAL_LEGACY)
endif()

if(${BUILD_DEBUG})
    set(CMAKE_BUILD_TYPE "Debug")
else()
    set(CMAKE_BUILD_TYPE "Release")
endif()

# print summary of configurations
message(STATUS "MCU_FAMILY: ${MCU_FAMILY}")
message(STATUS "MCU_NAME:   ${MCU_NAME}")
message(STATUS "Specified C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Build type:         ${CMAKE_BUILD_TYPE}")
message(STATUS "Linker script:      ${LINKER_SCRIPT}")
message(STATUS "Use LL library:     ${USE_LL_LIB}")
message(STATUS "Use HAL library:    ${USE_HAL_LIB}")
message(STATUS "Use LEGACY library: ${USE_HAL_LEGACY}")
message(STATUS "Use Segger SystemView library: ${USE_SYSTEM_VIEW}")

## version information
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")

include(${CMAKE_SOURCE_DIR}/cmake/stm32-gcc-flags.cmake)