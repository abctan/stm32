cmake_minimum_required(VERSION 3.0.0)
project(stm32demo C CXX ASM)

message(STATUS "-------------Building project: ${PROJECT_NAME} -------------")
set(STM32_CMAKE_DIR "${CMAKE_SOURCE_DIR}")

include(${STM32_CMAKE_DIR}/cmake/compile.cmake)

## add project components
set(ELF_TARGET ${PROJECT_NAME}.elf)
set(CMSIS_PATH ${PROJ_LIB_PATH}/STM32Cube_FW_F1_V1.8.0/Drivers/CMSIS)
set(STM32HAL_PATH ${PROJ_LIB_PATH}/STM32Cube_FW_F1_V1.8.0/Drivers/STM32F1xx_HAL_Driver)
set(CMSIC_INC ${CMSIS_PATH}/Include
              ${CMSIS_PATH}/Device/ST/STM32F1xx/Include
)

# add source folder
add_subdirectory(source)

include_directories(
    ${CMSIC_INC}
    ${STM32HAL_PATH}/Inc
    ${STM32_CMAKE_DIR}/source/app/main
    ${STM32_CMAKE_DIR}/source/driver/led
)
# STM32CubeMX generated source files
set(CUBEMX_SRC
    ${STM32_CMAKE_DIR}/source/app/main/main.c
    ${STM32_CMAKE_DIR}/source/app/main/stm32f1xx_it.c
    ${CMSIS_PATH}/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
)

add_executable(${ELF_TARGET} ${CUBEMX_SRC})
target_link_libraries(${ELF_TARGET} PUBLIC
    boot stm32f1xx_hal player led
)
target_link_libraries(${ELF_TARGET} PRIVATE -T${LINKER_SCRIPT} ${EXTRA_LINK_FLAGS})


## add post-build targets
include(${CMAKE_SOURCE_DIR}/cmake/stm32-gcc-postbuild.cmake)

# https://github.com/rxdu/stm32_cmake