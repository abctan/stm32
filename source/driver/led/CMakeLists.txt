set(C_FILE led.c)

set(H_FILE  ${HAL_CONF_PATH}
            ${CMSIC_INC}
            ${STM32HAL_PATH}/Inc
)

include_directories(${H_FILE})
add_library(led ${C_FILE})
target_link_libraries(led PUBLIC stm32f1xx_hal)