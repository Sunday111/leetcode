cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0973_k_closest_points_to_origin_tests
    0973.hpp
    0973_tests.cpp
)

target_link_libraries(0973_k_closest_points_to_origin_tests PUBLIC gtest_main)
set_generic_compiler_options(0973_k_closest_points_to_origin_tests PUBLIC)

target_link_libraries(0973_k_closest_points_to_origin_tests PRIVATE test_utility)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0973_k_closest_points_to_origin_tests)
