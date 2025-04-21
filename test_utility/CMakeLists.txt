cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

file(GLOB_RECURSE test_utility_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(test_utility INTERFACE ${test_utility_files})
target_link_libraries(test_utility INTERFACE gtest_main)
set_generic_compiler_options(test_utility INTERFACE)
