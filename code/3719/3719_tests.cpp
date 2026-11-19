#include "3719.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,5,4,3] 4

[3,2,2,5,4] 5

[1,2,3,2] 3
)cases");

using t3719 = SolutionTests<Solution>;

TEST_P(t3719, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestBalanced(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3719,
    t3719::parameters(kCases.size()),
    t3719::name);
