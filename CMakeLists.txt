cmake_minimum_required(VERSION 3.10)
project(bigfloat VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(bigfloat)
add_subdirectory(benchmark)
add_subdirectory(test)
enable_testing()
add_test(NAME bigfloat_tests COMMAND bigfloat_tests)