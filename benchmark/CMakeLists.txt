find_package(benchmark REQUIRED)

add_executable (run_benchmarks main.cpp nbody/nbody_sisd.hpp nbody/body.hpp nbody/util.hpp advanced.hpp shared.hpp helper.hpp)
target_compile_options(run_benchmarks PRIVATE -O3 -march=native)

target_link_libraries (run_benchmarks benchmark)
target_link_libraries (run_benchmarks bigfloat)
