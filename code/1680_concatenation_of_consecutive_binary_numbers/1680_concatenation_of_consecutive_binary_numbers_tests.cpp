#include "1680_concatenation_of_consecutive_binary_numbers.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::concatenatedBinary;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1

3 27

12 505379714

90999 459883164

100000 757631812
)cases");

using t1680_concatenation_of_consecutive_binary_numbers =
    SolutionTests<Solution>;

TEST_P(t1680_concatenation_of_consecutive_binary_numbers, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.concatenatedBinary(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1680_concatenation_of_consecutive_binary_numbers,
    t1680_concatenation_of_consecutive_binary_numbers::parameters(
        kCases.size()),
    t1680_concatenation_of_consecutive_binary_numbers::name);
