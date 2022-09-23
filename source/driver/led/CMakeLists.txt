set(C_FILE led.c)

set(H_FILE  ${HAL_CONF_PATH}
            ${CMSIS_PATH}/Core/Include
            ${CMSIS_PATH}/Device/ST/STM32F1xx/Include
            ${STM32HAL_PATH}/Inc
)

add_library(led ${C_FILE})
target_link_libraries(led PUBLIC stm32f1xx_hal)