add_library(bigfloat
        bigfloat.hpp
        bf.cpp
        bf.hpp
        math.hpp
        math.cpp
        vec4.hpp
        simd_vec4.cpp
        simd_vec4.hpp
        avx_helper.hpp
        sisd_vec4.cpp
        vec4.cpp
        mat4.cpp
        mat4.hpp helpers.inl interop/glm.hpp)
target_compile_options(bigfloat PUBLIC -mavx2)

