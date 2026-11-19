#include "1758_minimum_changes_to_make_alternating_binary_stringtest_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1758_minimum_changes_to_make_alternating_binary_string =
    SolutionTests<Solution>;

TEST_P(t1758_minimum_changes_to_make_alternating_binary_string, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1758_minimum_changes_to_make_alternating_binary_string,
    t1758_minimum_changes_to_make_alternating_binary_string::parameters(
        kCases.size()),
    t1758_minimum_changes_to_make_alternating_binary_string::name);
