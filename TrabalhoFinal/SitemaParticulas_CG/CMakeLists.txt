cmake_minimum_required(VERSION 2.8.4)
project(SitemaParticulas_CG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ps.cpp ps.h)
add_executable(SitemaParticulas_CG ${SOURCE_FILES})