cmake_minimum_required(VERSION 3.25)

include(set_compiler_options)

set(target_name 2138_divide_the_string_into_groups_of_size_k)
set(tests_target_name ${target_name}_tests)

add_library(${target_name} INTERFACE ${target_name}.hpp)
set_generic_compiler_options(${target_name} INTERFACE)

add_executable(${tests_target_name} ${target_name}_tests.cpp)

target_link_libraries(${tests_target_name} PUBLIC ${target_name} test_utility)
set_generic_compiler_options(${tests_target_name} PUBLIC)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${tests_target_name})

# add benchmark target if there any files with "_benchmark" suffix
file(GLOB_RECURSE benchmark_sources CONFIGURE_DEPENDS *_benchmark.cpp)
if (benchmark_sources)
    set(bench_target_name ${target_name}_bench)
    add_executable(${bench_target_name} ${benchmark_sources})
    target_link_libraries(${bench_target_name}
        PUBLIC
            ${target_name}
            benchmark::benchmark
            test_utility
    )
endif()
