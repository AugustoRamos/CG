cmake_minimum_required(VERSION 2.8.4)
project(TrabalhoCG1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BresenhamLine.cpp BresenhamLine.h BresenhamLine.cpp BresenhamLine.h)
add_executable(TrabalhoCG1 ${SOURCE_FILES} BresenhamLine.cpp BresenhamLine.h)