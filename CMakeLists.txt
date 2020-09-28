cmake_minimum_required(VERSION 3.10)
project(bigfloat)

set(CMAKE_CXX_STANDARD 17)
option(OPTIMIZE_FOR_NATIVE "Build with -march=native" ON)
if(OPTIMIZE_FOR_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

add_library(bigfloat bigfloat.hpp bf.cpp bf.hpp test/bigfloat_tests.cpp benchmark/main.cpp interop_mpfr.hpp math.hpp math.cpp interop_eigen.hpp simd.hpp bench_simd.cpp simd_vec4.cpp simd_vec4.hpp avx_helper.hpp sisd_vec4.cpp sisd_vec4.hpp boost_interop.hpp simd.cpp)
# target_link_libraries(bigfloat mpfr)

add_subdirectory(benchmark)

add_subdirectory(test)
enable_testing()
add_test(NAME bigfloat_tests COMMAND run_tests)