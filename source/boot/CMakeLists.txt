set(C_FILE  startup_stm32f103xe.s
            ${CMSIS_PATH}/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
            stm32f1xx_it.c)

set(H_FILE  ${CMAKE_SOURCE_DIR}/source/app/main
            ${CMSIS_PATH}/Include
            ${CMSIS_PATH}/Device/ST/STM32F1xx/Include)

include_directories(${H_FILE})

add_library(boot STATIC ${C_FILE})

target_compile_definitions(boot PUBLIC ${MCU_FAMILY})