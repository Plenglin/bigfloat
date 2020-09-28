add_library(bigfloat
        bigfloat.hpp
        bf.cpp
        bf.hpp
        interop_mpfr.hpp
        math.hpp
        math.cpp
        interop_eigen.hpp
        simd.hpp
        bench_simd.cpp
        simd_vec4.cpp
        simd_vec4.hpp
        avx_helper.hpp
        sisd_vec4.cpp
        sisd_vec4.hpp
        boost_interop.hpp
        simd.cpp)

target_compile_options(bigfloat PUBLIC -mavx2)
