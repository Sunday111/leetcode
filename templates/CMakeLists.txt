cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name templates_tests)
file(GLOB_RECURSE target_sources CONFIGURE_DEPENDS *.cpp)
add_executable(${target_name} ${target_sources})
target_link_libraries(${target_name} PUBLIC test_utility)
set_generic_compiler_options(${target_name} PUBLIC)
