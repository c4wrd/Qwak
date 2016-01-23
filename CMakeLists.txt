cmake_minimum_required(VERSION 3.3)
project(Qwak)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Token.cpp Token.h location.h)
add_executable(Qwak ${SOURCE_FILES})