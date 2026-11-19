#include "1784_test_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1784_check_if_binary_string_has_at_most_one_segment_of_ones =
    SolutionTests<Solution>;

TEST_P(
    t1784_check_if_binary_string_has_at_most_one_segment_of_ones,
    MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.checkOnesSegment(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1784_check_if_binary_string_has_at_most_one_segment_of_ones,
    t1784_check_if_binary_string_has_at_most_one_segment_of_ones::parameters(
        kCases.size()),
    t1784_check_if_binary_string_has_at_most_one_segment_of_ones::name);
