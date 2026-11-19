#include "3315.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minBitwiseArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,3,5,7] [-1,1,4,3]

[11,13,31] [9,12,15]
)cases");

using t3315 = SolutionTests<Solution>;

TEST_P(t3315, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minBitwiseArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3315,
    t3315::parameters(kCases.size()),
    t3315::name);
