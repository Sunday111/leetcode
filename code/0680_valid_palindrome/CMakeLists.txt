cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0680_valid_palindrome_tests
    0680_valid_palindrome.hpp
    0680_valid_palindrome_tests.cpp
)

target_link_libraries(0680_valid_palindrome_tests PUBLIC gtest_main)
set_generic_compiler_options(0680_valid_palindrome_tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0680_valid_palindrome_tests)
