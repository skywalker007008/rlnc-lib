cmake_minimum_required(VERSION 3.8)
project(rlnc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        gf.cpp
        gf.h codec.h codec.cpp)
add_executable(rlnc ${SOURCE_FILES})