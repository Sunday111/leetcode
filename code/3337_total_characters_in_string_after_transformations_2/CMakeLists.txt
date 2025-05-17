cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name 3337_total_characters_in_string_after_transformations_2_tests)

add_executable(${target_name}
    3337_total_characters_in_string_after_transformations_2.hpp
    3337_total_characters_in_string_after_transformations_2_tests.cpp
)

target_link_libraries(${target_name} PUBLIC test_utility)
set_generic_compiler_options(${target_name} PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${target_name})

set(benchmark_target 3337_benchmark)
add_executable(${benchmark_target} 3337_benchmark.cpp)
target_link_libraries(${benchmark_target} PUBLIC benchmark::benchmark test_utility)
set_generic_compiler_options(${benchmark_target} PUBLIC)
