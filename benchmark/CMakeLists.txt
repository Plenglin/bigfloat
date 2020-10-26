find_package(benchmark REQUIRED)

add_executable (bigfloat_benchmarks main.cpp nbody/nbody_sisd.hpp nbody/body.hpp nbody/util.hpp advanced.hpp shared.hpp bench_simd.h nbody/nbody_bf_simd.hpp)
target_compile_options(bigfloat_benchmarks PRIVATE -O3 -march=native)
target_include_directories(bigfloat_benchmarks PRIVATE ..)

target_link_libraries (bigfloat_benchmarks benchmark)
target_link_libraries (bigfloat_benchmarks bigfloat)
