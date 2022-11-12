file(GLOB STM32F1_HAL_SRC ${STM32HAL_PATH}/Src/stm32f1xx_hal*.c)
file(GLOB STM32F1_LL_SRC  ${STM32HAL_PATH}/Src/stm32f1xx_ll*.c)
if (USE_HAL_LEGACY)
    file(GLOB STM32F1_LEGACY_SRC ${STM32HAL_PATH}/Src/Legacy/*.c)
endif()

if(USE_HAL_LIB)
    set(STM32F1_LIB_SRC ${STM32F1_HAL_SRC} ${STM32F1_LEGACY_SRC})
else()
    set(STM32F1_LIB_SRC ${STM32F1_LL_SRC} ${STM32F1_LEGACY_SRC})
endif()

add_library(stm32f1xx_hal ${STM32F1_LIB_SRC})

target_include_directories(stm32f1xx_hal PUBLIC
    ${STM32HAL_PATH}/Inc
    ${CMSIC_INC}
    ${HAL_CONF_PATH}
)