set(START_UP startup_stm32f103xe.s
    # ${CMSIS_PATH}/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s
)
add_library(boot STATIC ${START_UP})