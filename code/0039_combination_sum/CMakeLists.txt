cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name 0039_combination_sum_tests)

add_executable(${target_name}
    0039_combination_sum.hpp
    0039_combination_sum_tests.cpp
)

target_link_libraries(${target_name} PUBLIC test_utility)
set_generic_compiler_options(${target_name} PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${target_name})

add_executable(0039_combination_sum_benchmark 0039_benchmark.cpp)
target_link_libraries(0039_combination_sum_benchmark benchmark::benchmark)
