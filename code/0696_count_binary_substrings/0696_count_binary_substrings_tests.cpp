#include "0696_count_binary_substrings.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countBinarySubstrings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"00110011" 6
)cases");

using t0696_count_binary_substrings = SolutionTests<Solution>;

TEST_P(t0696_count_binary_substrings, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countBinarySubstrings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0696_count_binary_substrings,
    t0696_count_binary_substrings::parameters(kCases.size()),
    t0696_count_binary_substrings::name);
