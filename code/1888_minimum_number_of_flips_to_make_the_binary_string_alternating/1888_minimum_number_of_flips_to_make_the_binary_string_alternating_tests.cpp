#include "1888_minimum_number_of_flips_to_make_the_binary_string_alternatingtest_cases.hpp"
#include "solution_tests.hpp"

using t1888_minimum_number_of_flips_to_make_the_binary_string_alternating =
    SolutionTests<Solution>;

TEST_P(
    t1888_minimum_number_of_flips_to_make_the_binary_string_alternating,
    MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minFlips(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1888_minimum_number_of_flips_to_make_the_binary_string_alternating,
    t1888_minimum_number_of_flips_to_make_the_binary_string_alternating::
        parameters(kCases.size()),
    t1888_minimum_number_of_flips_to_make_the_binary_string_alternating::name);
