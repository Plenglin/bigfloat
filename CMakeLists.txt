cmake_minimum_required(VERSION 3.10)
project(bigfloat)

set(CMAKE_CXX_STANDARD 17)
option(OPTIMIZE_FOR_NATIVE "Build with -march=native" ON)

add_subdirectory(benchmark)
add_subdirectory(src)
add_subdirectory(test)
enable_testing()
add_test(NAME bigfloat_tests COMMAND run_tests)