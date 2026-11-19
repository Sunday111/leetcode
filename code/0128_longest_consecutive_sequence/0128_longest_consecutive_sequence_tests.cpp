#include "0128_longest_consecutive_sequence.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestConsecutive;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[100,4,200,1,3,2] 4

[0,-1] 2
)cases");

using t0128_longest_consecutive_sequence = SolutionTests<Solution>;

TEST_P(t0128_longest_consecutive_sequence, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestConsecutive(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0128_longest_consecutive_sequence,
    t0128_longest_consecutive_sequence::parameters(kCases.size()),
    t0128_longest_consecutive_sequence::name);
