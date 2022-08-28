set(C_FILE hello.c)

set(H_FILE  ${CMAKE_CURRENT_SOURCE_DIR})

add_library(hello_drv ${C_FILE})
target_include_directories(hello_drv PUBLIC ${H_FILE})
