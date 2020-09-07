find_package(benchmark REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
add_executable (run_benchmarks bigfloat_benchmark.cpp)
target_compile_options(run_benchmarks PRIVATE -O3)

target_link_libraries (run_benchmarks benchmark)
target_link_libraries (run_benchmarks bigfloat)
