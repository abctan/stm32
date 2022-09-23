# Add libraries
add_library(cmsis INTERFACE)
target_compile_definitions(cmsis INTERFACE -D${MCU_FAMILY})
target_include_directories(cmsis INTERFACE
    ${CMSIS_PATH}/Core/Include
    ${CMSIS_PATH}/Device/ST/STM32F1xx/Include
)


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
if(USE_LL_LIB)
    target_compile_definitions(stm32f1xx_hal PUBLIC -DUSE_FULL_LL_DRIVER)
endif()
if(USE_HAL_LIB)
    target_compile_definitions(stm32f1xx_hal PUBLIC -DUSE_HAL_DRIVER)
endif()
target_link_libraries(stm32f1xx_hal PUBLIC cmsis)
target_include_directories(stm32f1xx_hal PUBLIC
    ${STM32HAL_PATH}/Inc
    ${HAL_CONF_PATH}
)