cmake_minimum_required(VERSION 3.16)
project(Butterfly_Project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_FLAGS "-O3 -g -fsanitize=address ") # 
include_directories(headers)

add_executable(Executable src/main.c)

target_link_libraries(Executable PRIVATE m)