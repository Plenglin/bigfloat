find_package(benchmark REQUIRED)

add_executable (run_benchmarks main.cpp nbody/nbody_sisd.hpp nbody/body.hpp nbody/util.hpp advanced.hpp shared.hpp bench_simd.h nbody/nbody_bf_simd.hpp)
target_compile_options(run_benchmarks PRIVATE -O3 -march=native)
target_include_directories(run_benchmarks PRIVATE ../include)

target_link_libraries (run_benchmarks benchmark)
target_link_libraries (run_benchmarks bigfloat)
