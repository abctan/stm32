cmake_minimum_required(VERSION 3.0.0)
project(stm32proj C CXX ASM)

message(STATUS "Building project: ${PROJECT_NAME}")
set(STM32_CMAKE_DIR "${CMAKE_SOURCE_DIR}")

# set the default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Build type: Debug")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Build type: Release")
endif()

include(${STM32_CMAKE_DIR}/cmake/compile.cmake)

## add project components
set(ELF_TARGET ${PROJECT_NAME}.elf)
set(CMSIS_PATH ${PROJ_LIB_PATH}/STM32Cube_FW_F1_V1.8.0/Drivers/CMSIS)
set(STM32HAL_PATH ${PROJ_LIB_PATH}/STM32Cube_FW_F1_V1.8.0/Drivers/STM32F1xx_HAL_Driver)
# add source folder
add_subdirectory(source)

include_directories(
    ${STM32_CMAKE_DIR}/source/app/main
    ${STM32_CMAKE_DIR}/source/driver/sys
    ${STM32_CMAKE_DIR}/source/driver/delay
    ${STM32_CMAKE_DIR}/source/driver/led
    ${STM32_CMAKE_DIR}/source/driver/usart
)
# STM32CubeMX generated source files
set(CUBEMX_SRC
    ${STM32_CMAKE_DIR}/source/app/main/main.c
)
add_executable(${ELF_TARGET} ${CUBEMX_SRC})
#target_compile_definitions(${ELF_TARGET} PUBLIC -D${MCU_FAMILY})
target_link_libraries(${ELF_TARGET} PUBLIC  -lc -lm -lnosys
    cmsis stm32f1xx_hal boot player
    led
)
target_link_libraries(${ELF_TARGET} PRIVATE -T${LINKER_SCRIPT} ${EXTRA_LINK_FLAGS})


## add post-build targets
include(${CMAKE_SOURCE_DIR}/cmake/stm32-gcc-postbuild.cmake)

# https://github.com/rxdu/stm32_cmake