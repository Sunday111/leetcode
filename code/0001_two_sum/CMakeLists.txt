cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0001_two_sum_tests
    0001_two_sum.hpp
    0001_two_sum_tests.cpp
)

target_link_libraries(0001_two_sum_tests PUBLIC gtest_main)
set_generic_compiler_options(0001_two_sum_tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0001_two_sum_tests)
