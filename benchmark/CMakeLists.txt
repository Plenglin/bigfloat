find_package(benchmark REQUIRED)

add_executable (run_benchmarks bigfloat_benchmark.cpp)
target_compile_options(run_benchmarks PRIVATE -O3 -march=native)

target_link_libraries (run_benchmarks benchmark)
target_link_libraries (run_benchmarks bigfloat)
