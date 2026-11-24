cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name lc_templates)
add_library(${target_name} INTERFACE)
set_generic_compiler_options(${target_name} INTERFACE)
target_compile_options(${target_name} INTERFACE -mtune=native -march=native)
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${target_name} INTERFACE LC_LOCAL_BUILD)
