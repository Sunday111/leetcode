cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(0273_integer_to_english_words_tests
    0273_integer_to_english_words.hpp
    0273_integer_to_english_words_tests.cpp
)

target_link_libraries(0273_integer_to_english_words_tests PUBLIC gtest_main)
set_generic_compiler_options(0273_integer_to_english_words_tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(0273_integer_to_english_words_tests)
