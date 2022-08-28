# cmake 最低版本
cmake_minimum_required(VERSION 3.16)

# 项目名称
project(demo)

# 查找当前目录文件
aux_source_directory(. DIR_SRCS)

# 添加目录
add_subdirectory(source)

# 生成可执行文件
add_executable(demo ${DIR_SRCS})

# 链接库
target_link_libraries(demo gpio)