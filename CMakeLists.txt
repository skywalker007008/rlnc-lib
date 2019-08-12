cmake_minimum_required(VERSION 3.8)
project(rlnc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        gf.cpp
        gf.h codec.h codec.cpp test_codec.cpp test_codec.h)
add_executable(rlnc ${SOURCE_FILES})