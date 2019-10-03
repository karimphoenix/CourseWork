cmake_minimum_required(VERSION 3.6)
project(courseWork)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RangeParametr.cpp RangeParametr.h)
add_executable(courseWork ${SOURCE_FILES})