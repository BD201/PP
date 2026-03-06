cmake_minimum_required(VERSION 3.12)
project("lab1" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1 
    lab1.cpp 
    Matrix.cpp
)

if(MSVC)
    target_link_options(lab1 PRIVATE "/STACK:67108864") 
else()
    target_link_options(lab1 PRIVATE "-Wl,--stack,67108864")  
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(lab1 PRIVATE /W4)
else()
    target_compile_options(lab1 PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")

message(STATUS "Project configured with stack size 16 MB")