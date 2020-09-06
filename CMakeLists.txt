cmake_minimum_required(VERSION 3.10)
project(bigfloat)

set(CMAKE_CXX_STANDARD 17)

add_library(bigfloat library.cpp library.h bigfloat.cpp bigfloat.hpp test/bigfloat_tests.cpp)
target_link_libraries(bigfloat mpfr)

add_subdirectory(test)
enable_testing()
add_test(NAME test1 COMMAND test)