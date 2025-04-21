cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name test_utility)
file(GLOB_RECURSE test_utility_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(${target_name} INTERFACE ${test_utility_files})
target_link_libraries(${target_name} INTERFACE gtest_main)
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_generic_compiler_options(${target_name} INTERFACE)
