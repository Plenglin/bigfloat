cmake_minimum_required(VERSION 3.10)
project(bigfloat)

set(CMAKE_CXX_STANDARD 17)

add_library(bigfloat library.cpp library.h bf.cpp bf.hpp test/bigfloat_tests.cpp benchmark/bigfloat_benchmark.cpp bigfloat_mpfr.h)
# target_link_libraries(bigfloat mpfr)

add_subdirectory(benchmark)

add_subdirectory(test)
enable_testing()
add_test(NAME bigfloat_tests COMMAND run_tests)