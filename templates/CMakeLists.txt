cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name lc_templates)
file(GLOB_RECURSE target_sources CONFIGURE_DEPENDS *.hpp)
add_library(${target_name} INTERFACE ${test_utility_files})
set_generic_compiler_options(${target_name} INTERFACE)
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set(tests_target_name ${target_name}_tests)
file(GLOB_RECURSE tests_sources CONFIGURE_DEPENDS *.cpp)
add_executable(${tests_target_name} ${tests_sources})
target_link_libraries(${tests_target_name} PUBLIC test_utility)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${tests_target_name})
