set(C_FILE src/player.c)

set(H_FILE  ${CMAKE_SOURCE_DIR}/source/include
            ${CMAKE_SOURCE_DIR}/source/common/inc)

include_directories(${H_FILE})

add_library(player STATIC ${C_FILE})