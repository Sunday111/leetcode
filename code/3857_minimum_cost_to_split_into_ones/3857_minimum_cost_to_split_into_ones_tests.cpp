#include "3857_minimum_cost_to_split_into_onestest_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t3857_minimum_cost_to_split_into_ones = SolutionTests<Solution>;

TEST_P(t3857_minimum_cost_to_split_into_ones, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3857_minimum_cost_to_split_into_ones,
    t3857_minimum_cost_to_split_into_ones::parameters(kCases.size()),
    t3857_minimum_cost_to_split_into_ones::name);
