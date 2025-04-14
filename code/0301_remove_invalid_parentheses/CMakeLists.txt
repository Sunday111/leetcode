cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0301_remove_invalid_parentheses_tests
    0301_remove_invalid_parentheses.hpp
    0301_remove_invalid_parentheses_tests.cpp
)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "clang")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG "@<MODULE_MAP_FILE>")

target_link_libraries(0301_remove_invalid_parentheses_tests PUBLIC gtest_main)
set_generic_compiler_options(0301_remove_invalid_parentheses_tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0301_remove_invalid_parentheses_tests)
