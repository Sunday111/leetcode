cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name abstract_iteration_benchmark)
add_executable(${target_name} abstract_iteration_benchmark.cpp)
target_link_libraries(${target_name} PUBLIC benchmark::benchmark test_utility)
set_generic_compiler_options(${target_name} PUBLIC)
