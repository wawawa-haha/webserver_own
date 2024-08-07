# 设置最低的CMake版本要求
cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/root/code/sm_own)

include_directories(/usr/include)

include_directories(/usr/local/include/)

find_package(yaml-cpp REQUIRED)

# 添加可执行文件
add_executable(x /root/code/sm_own/test.cpp 
                 /root/code/sm_own/log.cpp
                 /root/code/sm_own/util.cpp )


target_link_libraries(x yaml-cpp)


# 添加编译选项（如果需要）
# target_compile_options(x PRIVATE -Wall)

set(EXECUTABLE_OUTPUT_PATH /root/code/sm_own/bin)
