#include <tuple>

#include "3666_minimum_operations_to_equalize_binary_string.hpp"
#include "solution_tests.hpp"
#include "test_cases.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases =
    parse_test_cases<&Solution::minOperations>(kTestCases);

using T3666Test = SolutionTests<Solution>;

TEST_P(T3666Test, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    T3666Test,
    T3666Test::parameters(kCases.size()),
    T3666Test::name);
