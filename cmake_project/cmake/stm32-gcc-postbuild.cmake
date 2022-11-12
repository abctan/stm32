# name of targets
set(BIN_TARGET ${PROJECT_NAME}.bin)
set(HEX_TARGET ${PROJECT_NAME}.hex)
set(MAP_TARGET ${PROJECT_NAME}.map)
set(LSS_TARGET ${PROJECT_NAME}.lss)

# create binary & hex files and show size of resulting firmware image
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex      $<TARGET_FILE:${PROJECT_NAME}.elf>   ${HEX_TARGET}
        COMMAND ${CMAKE_OBJCOPY} -Obinary    $<TARGET_FILE:${PROJECT_NAME}.elf>   ${BIN_TARGET}
        COMMAND ${ARM_OBJDUMP_EXECUTABLE} -S $<TARGET_FILE:${PROJECT_NAME}.elf> > ${LSS_TARGET}

        COMMENT "Building ${BIN_TARGET} and ${HEX_TARGET}"
        COMMAND ${CMAKE_COMMAND} -E copy ${HEX_TARGET} "${EXE_OUTPUT_PATH}/${HEX_TARGET}"
        COMMAND ${CMAKE_COMMAND} -E copy ${BIN_TARGET} "${EXE_OUTPUT_PATH}/${BIN_TARGET}"
        COMMAND ${CMAKE_COMMAND} -E copy ${LSS_TARGET} "${EXE_OUTPUT_PATH}/${LSS_TARGET}"

        COMMAND ${ARM_SIZE_EXECUTABLE} -B ${ELF_TARGET} ${HEX_TARGET}
        COMMENT "Invoking: Cross ARM GNU Print Size"
)