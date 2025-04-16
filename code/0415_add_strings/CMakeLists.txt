cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0415_add_strings_tests
    0415_add_strings.hpp
    0415_add_strings_tests.cpp
)

target_link_libraries(0415_add_strings_tests PUBLIC gtest_main)
set_generic_compiler_options(0415_add_strings_tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0415_add_strings_tests)
