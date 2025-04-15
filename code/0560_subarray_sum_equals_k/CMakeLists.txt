cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0560_subarray_sum_equals_k_tests
    0560_subarray_sum_equals_k.hpp
    0560_subarray_sum_equals_k_tests.cpp
)

target_link_libraries(0560_subarray_sum_equals_k_tests PUBLIC gtest_main)
set_generic_compiler_options(0560_subarray_sum_equals_k_tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0560_subarray_sum_equals_k_tests)
