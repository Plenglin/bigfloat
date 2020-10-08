cmake_minimum_required(VERSION 3.10)
project(bigfloat VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)

add_library(bigfloat
        include/bigfloat.hpp
        src/bf.cpp
        include/bf.hpp
        include/math.hpp
        src/math.cpp
        include/simd.hpp
        src/simd_vec4.cpp
        include/simd_vec4.hpp
        include/avx_helper.hpp
        src/sisd_vec4.cpp
        src/simd.cpp)
target_include_directories(bigfloat PRIVATE src PUBLIC include)
target_compile_options(bigfloat PUBLIC -mavx2)

add_subdirectory(benchmark)
add_subdirectory(test)
enable_testing()
add_test(NAME bigfloat_tests COMMAND run_tests)