add_library(bigfloat
        bigfloat.hpp
        bf.cpp
        bf.hpp
        math.hpp
        math.cpp
        simd.hpp
        simd_vec4.cpp
        simd_vec4.hpp
        avx_helper.hpp
        sisd_vec4.cpp
        simd.cpp
        mat_4.cpp
        mat_4.hpp)
target_compile_options(bigfloat PUBLIC -mavx2)

