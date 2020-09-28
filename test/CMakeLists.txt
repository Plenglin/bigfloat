set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

add_executable (run_tests bigfloat_tests.cpp simd_vec4_tests.cpp _include.hpp helper_tests.cpp vecn_tests.cpp)
target_link_libraries (run_tests ${Boost_LIBRARIES})
target_link_libraries (run_tests bigfloat)
