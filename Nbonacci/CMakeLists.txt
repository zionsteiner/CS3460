cmake_minimum_required(VERSION 3.16)
project(Nbonacci)

set(CMAKE_CXX_STANDARD 17)

add_executable(Nbonacci Assignment1.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Nbonacci PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Nbonacci PRIVATE -Wall -Wextra -pedantic)
endif()