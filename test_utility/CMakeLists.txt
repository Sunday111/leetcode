cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name test_utility)
file(GLOB_RECURSE test_utility_hdr CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE test_utility_src CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${target_name} STATIC ${test_utility_hdr} ${test_utility_src})
target_link_libraries(${target_name} PUBLIC gtest lc_templates)
target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_generic_compiler_options(${target_name} PUBLIC)

# Debug with sanitizers 🤌
target_compile_options(${target_name} INTERFACE $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
target_link_options(${target_name} INTERFACE $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
