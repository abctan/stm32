set(C_FILE  startup_stm32f103xe.s
            stm32f1xx_it.c
            ${CMSIS_PATH}/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
)

set(H_FILE  ${CMAKE_SOURCE_DIR}/source/app/main
            ${CMSIS_PATH}/Include
            ${CMSIS_PATH}/Device/ST/STM32F1xx/Include
            ${STM32HAL_PATH}/Inc
)

include_directories(${H_FILE})

add_library(boot STATIC ${C_FILE})