cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name 2246_longest_path_with_different_adjacent_characters_tests)

add_executable(${target_name}
    2246_longest_path_with_different_adjacent_characters.hpp
    2246_longest_path_with_different_adjacent_characters_tests.cpp
)

target_link_libraries(${target_name} PUBLIC test_utility)
set_generic_compiler_options(${target_name} PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${target_name})
