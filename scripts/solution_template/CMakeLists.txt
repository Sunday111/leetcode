cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

add_executable(____problem_name_____tests
    ____problem_name____.hpp
    ____problem_name_____tests.cpp
)

target_link_libraries(____problem_name_____tests PUBLIC gtest_main)
set_generic_compiler_options(____problem_name_____tests PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(____problem_name_____tests)
