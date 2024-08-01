# 设置最低的CMake版本要求
cmake_minimum_required(VERSION 3.10)

message(STATUS "Source files: ${SOURCE_FILES}")

# 设置项目名称
project(MyProject)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(x test.cpp)

# 指定头文件的目录
# 如果你有多个头文件目录，可以用 'include_directories' 添加
target_include_directories(x PRIVATE /root/code/sw_own)

# 添加编译选项（如果需要）
# target_compile_options(x PRIVATE -Wall)

set(EXECUTABLE_OUTPUT_PATH /root/code/sm_own/bin)
