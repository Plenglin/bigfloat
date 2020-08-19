cmake_minimum_required(VERSION 3.17)
project(bigfloat)

set(CMAKE_CXX_STANDARD 17)

add_library(bigfloat library.cpp library.h bigfloat.cpp bigfloat.h)