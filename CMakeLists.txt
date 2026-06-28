cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

project(data_structure VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14) # make_unique support starts from 14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #NOTE to export `compile_commands.json` for clangd to process intellisense

set(CXX_SRCS) # source files list

# CMAKE三阶段：configure(配置)->build(编译)->(install(安装)，可忽略)
# 手动维护。这样cmake编译时检测到CMakeLists.txt改动，会自动configure再编译
list(APPEND CXX_SRCS
    ./linear_list/sequence_list.hpp # work dir is current dir of current CMakeLists.txt: ${CMAKE_CURRENT_SOURCE_DIR}
    ./linear_list/linked_list.hpp
    ./utils.hpp
    ./main.cpp
)


add_executable(data_structure ${CXX_SRCS})
target_include_directories(data_structure PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 我们可以先注释掉复杂点的源码，执行一次configure，获取compile_commands.json，获取通用函数源码的路径后，再解注释具体源码。
# 这样即可再具体源码中使用通用函数
