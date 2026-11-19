#include "1689_test_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1689_partitioning_into_minimum_number_of_decibinary_numbers =
    SolutionTests<Solution>;

TEST_P(
    t1689_partitioning_into_minimum_number_of_decibinary_numbers,
    MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minPartitions(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1689_partitioning_into_minimum_number_of_decibinary_numbers,
    t1689_partitioning_into_minimum_number_of_decibinary_numbers::parameters(
        kCases.size()),
    t1689_partitioning_into_minimum_number_of_decibinary_numbers::name);
