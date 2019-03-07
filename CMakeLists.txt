cmake_minimum_required(VERSION 3.13)
project(string)

set(CMAKE_CXX_STANDARD 17)

add_library(string string_helper.cpp string_helper.h string.h string.cpp)